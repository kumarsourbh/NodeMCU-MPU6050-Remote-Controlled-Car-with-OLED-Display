// Written by Sourbh Kumar, YouTube Channel: https://www.youtube.com/@Learnroboticswithsourbh
// Acknowledgment: Libraries by Adafruit, Jeff Rowberg, and Espressif Systems


#include <ESP8266WiFi.h>
#include <espnow.h>

// GPIO pins for motors
#define MOTOR_UL1 D0 // Upper Left Motor - Pin 1
#define MOTOR_UL2 D1 // Upper Left Motor - Pin 2
#define MOTOR_LL1 D2 // Lower Left Motor - Pin 1
#define MOTOR_LL2 D3 // Lower Left Motor - Pin 2
#define MOTOR_UR1 D4 // Upper Right Motor - Pin 1
#define MOTOR_UR2 D5 // Upper Right Motor - Pin 2
#define MOTOR_LR1 D6 // Lower Right Motor - Pin 1
#define MOTOR_LR2 D7 // Lower Right Motor - Pin 2

void setupMotors() {
  // Configure motor pins as output
  pinMode(MOTOR_UL1, OUTPUT);
  pinMode(MOTOR_UL2, OUTPUT);
  pinMode(MOTOR_LL1, OUTPUT);
  pinMode(MOTOR_LL2, OUTPUT);
  pinMode(MOTOR_UR1, OUTPUT);
  pinMode(MOTOR_UR2, OUTPUT);
  pinMode(MOTOR_LR1, OUTPUT);
  pinMode(MOTOR_LR2, OUTPUT);
}

void stopMotors() {
  digitalWrite(MOTOR_UL1, LOW);
  digitalWrite(MOTOR_UL2, LOW);
  digitalWrite(MOTOR_LL1, LOW);
  digitalWrite(MOTOR_LL2, LOW);
  digitalWrite(MOTOR_UR1, LOW);
  digitalWrite(MOTOR_UR2, LOW);
  digitalWrite(MOTOR_LR1, LOW);
  digitalWrite(MOTOR_LR2, LOW);
}

void moveForward() {
  digitalWrite(MOTOR_UL1, HIGH);
  digitalWrite(MOTOR_UL2, LOW);
  digitalWrite(MOTOR_LL1, HIGH);
  digitalWrite(MOTOR_LL2, LOW);
  digitalWrite(MOTOR_UR1, HIGH);
  digitalWrite(MOTOR_UR2, LOW);
  digitalWrite(MOTOR_LR1, HIGH);
  digitalWrite(MOTOR_LR2, LOW);
}

void moveBackward() {
  digitalWrite(MOTOR_UL1, LOW);
  digitalWrite(MOTOR_UL2, HIGH);
  digitalWrite(MOTOR_LL1, LOW);
  digitalWrite(MOTOR_LL2, HIGH);
  digitalWrite(MOTOR_UR1, LOW);
  digitalWrite(MOTOR_UR2, HIGH);
  digitalWrite(MOTOR_LR1, LOW);
  digitalWrite(MOTOR_LR2, HIGH);
}

void moveLeft() {
  digitalWrite(MOTOR_UL1, LOW);
  digitalWrite(MOTOR_UL2, HIGH);
  digitalWrite(MOTOR_LL1, HIGH);
  digitalWrite(MOTOR_LL2, LOW);
  digitalWrite(MOTOR_UR1, HIGH);
  digitalWrite(MOTOR_UR2, LOW);
  digitalWrite(MOTOR_LR1, LOW);
  digitalWrite(MOTOR_LR2, HIGH);
}

void moveRight() {
  digitalWrite(MOTOR_UL1, HIGH);
  digitalWrite(MOTOR_UL2, LOW);
  digitalWrite(MOTOR_LL1, LOW);
  digitalWrite(MOTOR_LL2, HIGH);
  digitalWrite(MOTOR_UR1, LOW);
  digitalWrite(MOTOR_UR2, HIGH);
  digitalWrite(MOTOR_LR1, HIGH);
  digitalWrite(MOTOR_LR2, LOW);
}

void onReceive(uint8_t *mac, uint8_t *data, uint8_t len) {
  String command = "";
  for (int i = 0; i < len; i++) {
    command += (char)data[i];
  }
  Serial.println("Received Command: " + command);

  // Execute motor action based on the command
  if (command == "FORWARD") {
    moveForward();
  } else if (command == "BACKWARD") {
    moveBackward();
  } else if (command == "LEFT") {
    moveLeft();
  } else if (command == "RIGHT") {
    moveRight();
  } else if (command == "STOP") {
    stopMotors();
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // Set device as Station (STA) mode

  // Initialize motors
  setupMotors();
  stopMotors(); // Ensure motors are stopped initially

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW Initialization Failed!");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE); // Set as Receiver
  esp_now_register_recv_cb(onReceive); // Register callback for incoming data

  Serial.println("Car is ready to receive commands...");
}

void loop() {
  // No need for loop code, commands are handled in the callback
}
