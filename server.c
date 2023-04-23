#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libserialport.h>

void list_ports() {
    struct sp_port **ports;
    enum sp_return result = sp_list_ports(&ports);

    if (result != SP_OK) {
        printf("Error: Unable to list serial ports.\n");
        exit(1);
    }

    for (int i = 0; ports[i]; i++) {
        printf("Port: %s\n", sp_get_port_name(ports[i]));
    }

    sp_free_port_list(ports);
}

struct sp_port *connect_to_port(const char *port_name) {
    struct sp_port *port;
    enum sp_return result = sp_get_port_by_name(port_name, &port);

    if (result != SP_OK) {
        printf("Error: Unable to find the specified port.\n");
        exit(1);
    }

    result = sp_open(port, SP_MODE_READ_WRITE);
    if (result != SP_OK) {
        printf("Error: Unable to open the specified port.\n");
        exit(1);
    }

    sp_set_baudrate(port, 9600);
    sp_set_bits(port, 8);
    sp_set_parity(port, SP_PARITY_NONE);
    sp_set_stopbits(port, 1);
    sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE);

    return port;
}

void send_command(struct sp_port *port, const char *command) {
    enum sp_return result = sp_blocking_write(port, command, strlen(command), 0);
    if (result < 0) {
        printf("Error: Unable to send command.\n");
        exit(1);
    }
}

void read_response(struct sp_port *port) {
    char response[64];
    int bytes_read = sp_blocking_read_next(port, response, sizeof(response) - 1, 1000);
    if (bytes_read < 0) {
        printf("Error: Unable to read response.\n");
        exit(1);
    }
    response[bytes_read] = '\0';
    printf("Response: %s", response);
}

int main() {
    printf("Available serial ports:\n");
    list_ports();

    printf("\nEnter the port to connect (e.g., COM3 or /dev/ttyACM0): ");
    char port_name[64];
    fgets(port_name, sizeof(port_name), stdin);
    port_name[strcspn(port_name, "\n")] = '\0'; // Remove newline character

    struct sp_port *port = connect_to_port(port_name);
    printf("Connected to %s\n", port_name);

    while (1) {
        printf("\nEnter command (1 to turn LED on, 0 to turn LED off, q to quit): ");
        char command[2];
        fgets(command, sizeof(command), stdin);
        getchar(); // Consume newline character

        if (command[0] == 'q') {
            break;
        } else if (command[0] == '1' || command[0] == '0') {
            send_command(port, command);
            read_response(port);
        } else {
            printf("Invalid command. Please enter 1, 0, or q.\n");
        }
    }

    sp_close(port);
    printf("Disconnected from %s\n", port_name);

    return 0;
}
