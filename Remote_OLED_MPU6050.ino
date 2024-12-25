// Written by Sourbh Kumar, YouTube Channel: https://www.youtube.com/@Learnroboticswithsourbh
// Acknowledgment: Libraries by Adafruit, Jeff Rowberg, and Espressif Systems

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <MPU6050.h>

// OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Create OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Initialize MPU6050
MPU6050 mpu;

// MAC Address of the Car NodeMCU (Receiver)
uint8_t carMACAddress[] = {0x98, 0xF4, 0xAB, 0xD9, 0x09, 0xB4}; // Replace it with your MAC address

// Variables for accelerometer and gyroscope data
int16_t ax, ay, az;
int16_t gx, gy, gz;

// Function to send a command
void sendCommand(String cmd) {
  esp_now_send(carMACAddress, (uint8_t *)cmd.c_str(), cmd.length());
  Serial.println("Command Sent: " + cmd);
}

// ESP-NOW callback function
void onSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Command sent: ");
  Serial.println(sendStatus == 0 ? "Success" : "Fail");
}

// Function to display command on OLED
void displayCommand(const char *command) {
  display.clearDisplay();
  display.setTextSize(2);             // Set text size
  display.setTextColor(SSD1306_WHITE); // Set text color
  display.setCursor(0, 20);           // Set position
  display.println(command);           // Print command
  display.display();                  // Display the text
}

// Function to display large text (for SK)
void displayLargeText(const char *text) {
  display.setTextSize(3);             // Set text size for large text
  display.setTextColor(SSD1306_WHITE); // Set text color
  display.setCursor(0, 0);            // Set position
  display.println(text);              // Print text
  display.display();                  // Display the text
}

void setup() {
  Serial.begin(115200);

  // Initialize I2C communication
  Wire.begin(D2, D1);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED initialization failed!");
    while (true); // Stop execution if OLED is not initialized
  }

  // Show "SK" text
  display.clearDisplay();
  displayLargeText("SK");
  delay(1000);

  // Initialize MPU6050
  Serial.println("Initializing MPU6050...");
  mpu.initialize();
  display.clearDisplay();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 Initialized!");
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("MPU6050 Initialized!");
  } else {
    Serial.println("MPU6050 NOT Found!");
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("MPU6050 NOT Found!");
  }
  display.display();
  delay(2000);

  // Set up ESP-NOW
  WiFi.mode(WIFI_STA); // Set as Station mode
  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW Initialization Failed!");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER); // Set as Controller
  esp_now_add_peer(carMACAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  Serial.println("Remote is ready to send commands...");
}

void loop() {
  // Read accelerometer and gyroscope data
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Determine motion and send appropriate commands
  if (ax > 15000) { // Tilt forward
    sendCommand("FORWARD");
    displayCommand("FORWARD");
    Serial.println("FORWARD");
    delay(500);
  } else if (ax < -15000) { // Tilt backward
    sendCommand("BACKWARD");
    displayCommand("BACKWARD");
    Serial.println("BACKWARD");
    delay(500);
  } else if (ay > 15000) { // Tilt right
    sendCommand("RIGHT");
    displayCommand("RIGHT");
    Serial.println("RIGHT");
    delay(500);
  } else if (ay < -15000) { // Tilt left
    sendCommand("LEFT");
    displayCommand("LEFT");
    Serial.println("LEFT");
    delay(500);
  } else { // No significant motion
    sendCommand("STOP");
    displayCommand("STOP");
    Serial.println("STOP");
    delay(500);
  }

  // Debugging output in Serial Monitor
  delay(500); // Delay to avoid rapid updates
}
