# Arduino Uno Serial Communication

This project demonstrates serial communication between an Arduino Uno and a computer using a C program and the libserialport library. The provided C program can send commands to the Arduino Uno to control the built-in LED (turn it on or off) and read responses from the Arduino.
Requirements

## Arduino Uno
* USB cable to connect Arduino Uno to the computer
* libserialport library installed on your computer
* GCC compiler (for Linux/macOS) or MinGW (for Windows)

# Arduino Sketch

Upload the provided Arduino sketch (arduino_serial.ino) to your Arduino Uno using the Arduino IDE. This sketch listens for commands via serial communication and controls the built-in LED based on the received commands. It also sends responses back to the computer.
C Program

The provided C program (serial_example.c) uses the libserialport library to communicate with the Arduino Uno via a serial connection. It sends commands to turn the built-in LED on or off and reads the responses from the Arduino Uno.
Compilation

## To compile the C program, use the following command:

for linux:

    gcc serial_example.c -o serial_example -lserialport

for windows:

    gcc serial_example.c -o serial_example.exe -lserialport

## Usage

 1. Connect your Arduino Uno to your computer using a USB cable.

 2. Run the compiled C program:

 Linux/macOS:


      ./serial_example

Windows:

      serial_example.exe

3. When prompted, enter the name of the serial port that your Arduino Uno is connected to (e.g., "COM3" on Windows or "/dev/ttyACM0" on Linux/macOS).

4. Send commands to control the Arduino Uno (e.g., "1" to turn on the built-in LED, "0" to turn it off). Enter "q" to quit the program and disconnect from the port.
