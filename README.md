# NavAssist

NavAssist is an assistive device designed to help visually impaired individuals navigate their environment safely. It uses ultrasonic sensors, servo motors, and ESP32 microcontrollers to detect obstacles and provide real-time haptic feedback via a buzzer.

## Features

- **Obstacle Detection:** Four ultrasonic sensors scan for obstacles in multiple directions.
- **Dynamic Scanning:** Each sensor is mounted on a servo motor for adjustable scanning angles.
- **Wireless Communication:** ESP32 WROOM Devkit sends obstacle data wirelessly to a Seeed Studio Xiao C3.
- **Haptic Feedback:** The Xiao C3 triggers a buzzer to alert the user upon obstacle detection.
- **Portable:** Powered by a 3.7V battery for easy mobility.

## Hardware Requirements

To build NavAssist, you will need:

- **4x Servo Motors** (for rotating the ultrasonic sensors)
- **4x Ultrasonic Sensors** (for detecting obstacles)
- **1x ESP32 WROOM Devkit** (main controller; scans environment and sends data)
- **1x Seeed Studio Xiao C3** (secondary controller; receives signals and triggers feedback)
- **1x Buzzer Module** (for haptic/audio alerts)
- **1x 3.7V Battery** (for portable power supply)
- **Connecting wires, stick/frame for mounting components**

## How It Works

1. Ultrasonic sensors, mounted on servos, continuously scan for obstacles.
2. The ESP32 processes sensor data and sends a signal when an obstacle is detected.
3. The Seeed Studio Xiao C3 receives the signal and activates the buzzer.
4. The buzzer provides haptic feedback to alert the user.

## Setup Instructions

1. **Hardware Assembly**
   - Mount the ultrasonic sensors on servos and fix them to the stick/frame.
   - Connect servos and sensors to the ESP32 WROOM Devkit.
   - Set up wireless communication between ESP32 and Xiao C3.
   - Connect the buzzer module to the Xiao C3.
   - Power the system using the 3.7V battery.

2. **Software**
   - Upload the ESP32 code to the WROOM Devkit.
   - Upload the receiver code to the Xiao C3.
   - (Refer to the `/src` folder for example code.)

3. **Testing**
   - Power on the device and move objects in front of the sensors.
   - The buzzer should activate when obstacles are detected.

## Troubleshooting

- **No buzzer sound:** Check wiring and power to Xiao C3 and buzzer module.
- **Sensors not detecting:** Verify connections and sensor orientation. Upload code again if necessary.
- **Servos not moving:** Confirm servo connections and power supply.

## Contributing

Contributions are welcome! Please open issues or submit pull requests for improvements.

## License

This project is licensed under the [MIT License](LICENSE).

---

*For questions or support, please open an issue in this repository.*
