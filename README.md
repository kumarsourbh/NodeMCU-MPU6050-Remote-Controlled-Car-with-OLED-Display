# NodeMCU-MPU6050-Remote-Controlled-Car-with-OLED-Display
This project demonstrates how to build a remote-controlled car using a NodeMCU ESP8266, an MPU6050 accelerometer and gyroscope module, and an SSD1306 OLED display. The car utilizes the data from the MPU6050 to control its multi-directional motion using mecanum wheels.
Features

Wireless Control: Uses ESP-NOW for real-time, low-latency communication.
Motion-Based Commands: Tilt the MPU6050 sensor to send directional commands (FORWARD, BACKWARD, LEFT, RIGHT, STOP).
OLED Feedback: Displays the status of commands and the connection status of the MPU6050.
Compact Design: Combines multiple features into a single, easy-to-implement project.

###Hardware Requirements

NodeMCU ESP8266 (2 units: one for the remote, one for the car)
MPU6050 Accelerometer and Gyroscope Sensor
SSD1306 OLED Display (128x64 resolution)
Mecanum Wheels with Motors (4 units)
Motor Driver Module
Power Supply (Battery pack for the car and NodeMCU)
Jumper Wires and Breadboard for prototyping
Software Requirements
Arduino IDE (Latest version)
ESP8266 Board Manager (Add through Arduino IDE preferences)
Required Libraries:
Adafruit GFX Library (Download Link)
Adafruit SSD1306 Library (Download Link)
MPU6050 Library (Download Link)
ESP8266WiFi (Built into the ESP8266 board package)
ESP-NOW (Built into the ESP8266 board package)
Circuit Diagram
The complete wiring diagram is included in the repository as Circuit_Diagram.png for both:

Remote Module (NodeMCU + MPU6050 + OLED)
Car Module (NodeMCU + Motor Driver + Mecanum Wheels)
Ensure proper connections as per the diagram for seamless operation.

###Project Workflow
Initialization:

On powering up, the OLED displays "SK" followed by the status of the MPU6050.

###Motion Detection:

The MPU6050 detects tilt in the X and Y axes.
Based on the tilt, motion commands are sent to the car via ESP-NOW.

###Command Execution:

The car receives commands and moves in the corresponding direction using mecanum wheels.
Command status is displayed on the OLED in real time.

Setup Instructions

Install the required libraries in the Arduino IDE.
Add the ESP8266 board to the Arduino IDE via the Board Manager.
Open the Remote and Car sketches from this repository in the Arduino IDE.
Replace the MAC address in the remote code with the MAC address of the car NodeMCU.
Upload the respective sketches to the NodeMCU boards.
Assemble the circuit as per the provided circuit diagram.
Power the modules and enjoy the motion-based remote-controlled car.

###Commands

FORWARD: Tilt the remote forward.  
BACKWARD: Tilt the remote backward.  
LEFT: Tilt the remote left.  
RIGHT: Tilt the remote right.  
STOP: Keep the remote level.  
Future Improvements  
Add obstacle detection using ultrasonic sensors.  
Extend functionality with a mobile app for additional control options.  
Incorporate more sophisticated motion algorithms for smoother transitions.  

###Acknowledgments    
Adafruit for the excellent libraries and OLED support.  
Jeff Rowberg for the MPU6050 library.  
Espressif for the robust ESP-NOW communication protocol.  

### Setup - Circuit Diagram for both Remote Side and CAR Side - AP Mode  
![CAR Side_bb](https://github.com/user-attachments/assets/bf91b955-b2ee-4857-98e0-400b7bb1b6f4)  
![Remote_bb](https://github.com/user-attachments/assets/73d0cd08-cecb-4068-8629-1ec94f0e1ffb)



###License

This project is licensed under the MIT License. See the LICENSE file for details.
