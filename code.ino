void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char received = Serial.read();
    if (received == '1') {
      digitalWrite(13, HIGH);
      Serial.println("LED ON");
    } else if (received == '0') {
      digitalWrite(13, LOW);
      Serial.println("LED OFF");
    }
  }
}
