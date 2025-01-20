# Project GARUDA

## Brief Introduction

GARUDA is an advanced environmental monitoring system combining a rover and drone equipped with sensors to protect ecosystems and wildlife. It provides real-time data on fire detection, water safety, illegal logging, litter cleanup, and wildlife injury detection. Powered by solar energy with backup battery support, GARUDA operates autonomously or via remote control, ensuring sustainability and flexibility. By alerting authorities and contributing to conservation efforts, GARUDA plays a crucial role in preserving natural habitats and improving ecosystem health.

---

## Concept Map


# Project GARUDA

## Workflow Diagram

### Initialization:
- Power On → Check Power Supply → Initialize Rover & Drone

### Monitoring:
- Start Monitoring → Determine Monitoring Type (Fire Detection, Water Safety, Illegal Logging, Litter Cleanup, Wildlife Protection)

### Action:
- Fire Detection → Drone: Fire Sensor Activation
- Water Safety → Rover: Monitor Water Quality
- Illegal Logging → Drone: Camera & Sensors for Logging
- Litter Cleanup → Rover: Detect and Collect Litter
- Wildlife Protection → Infrared Detection for Injured Animals

### Data Transmission:
- Send Data to Ground Station → Real-time Data Analysis → Immediate Action by Authorities

---

## Tech Stack of Project GARUDA

### Rover
- **Microcontroller:** Arduino Mega (primary brain for data management and control)
- **Motor Control:** 10kg torque gear motor with motor drive module (for movement)
- **Navigation:** GPS module (for location tracking)
- **Obstacle Detection:** Ultrasonic sensors (for detecting obstacles)
- **Power Supply:** Solar panel (primary), battery (backup)
- **Wheels:** Off-road 4-inch wheels (for terrain adaptability)
- **Surveillance:** Infrared and normal cameras (for monitoring)
- **Environmental Monitoring:** Temperature and humidity sensors (for data collection)
- **Crane Control:** Servo motor and driver (for crane operations)
- **Door Operation:** Hydraulic motor (for door movement)
- **Manual Control:** NRF24L01 (for remote control)

### Drone
- **Flight Controller:** PIXHAWK (brain of the drone, pre-programmed and manual control)
- **Telemetry:** Data transmission from drone to ground station
- **Surveillance:** Infrared and night vision cameras (for identifying living vs. non-living objects)
- **Fire Detection:** Fire sensor (for early fire detection)
- **Manual Control:** Remote control option for manual operation

---

## Novelty of GARUDA

- **Dual-system operation:** The rover and drone work together, providing ground and aerial monitoring capabilities.
- **Autonomous and manual control:** The rover and drone can operate autonomously or be manually controlled, enhancing flexibility.
- **Comprehensive sensor suite:** GARUDA uses GPS, ultrasonic sensors, infrared cameras, fire sensors, and environmental monitors (temperature, humidity) for a wide range of applications.
- **Energy efficiency:** Powered primarily by solar energy with battery backup, ensuring sustainability for long-duration missions.
- **Wildlife protection:** It can detect injured animals and alert authorities, contributing directly to wildlife conservation efforts.

---

## Solution of GARUDA

- **Fire Detection:** The drone detects fires early, alerting authorities to prevent wildfires.
- **Water Safety:** Monitors water bodies for pollution and unsafe conditions.
- **Illegal Logging:** Uses cameras and sensors to detect illegal logging activities.
- **Litter Cleanup:** Detects and assists in removing litter from remote areas.
- **Wildlife Injury Detection:** Identifies injured animals using infrared and night vision, alerting officials for rescue.
- **Sustainable Operation:** Powered by solar energy with battery backup for long-term, eco-friendly use.
- **Real-time Monitoring:** Transmits data to a central station for immediate action and decision-making.

---

## GARUDA Features

- **Dual-system operation:** The rover and drone work together, providing ground and aerial monitoring capabilities.
- **Autonomous and manual control:** The rover and drone can operate autonomously or be manually controlled, enhancing flexibility.
- **Comprehensive sensor suite:** GARUDA uses GPS, ultrasonic sensors, infrared cameras, fire sensors, and environmental monitors (temperature, humidity) for a wide range of applications.
- **Energy efficiency:** Powered primarily by solar energy with battery backup, ensuring sustainability for long-duration missions.
- **Wildlife protection:** It can detect injured animals and alert authorities, contributing directly to wildlife conservation efforts.

