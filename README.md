# Brief Introduction
GARUDA is an advanced environmental monitoring system combining a rover and drone equipped with sensors to protect ecosystems and wildlife. It provides real-time data on fire detection, water safety, illegal logging, litter cleanup, and wildlife injury detection. Powered by solar energy with backup battery support, GARUDA operates autonomously or via remote control, ensuring sustainability and flexibility. By alerting authorities and contributing to conservation efforts, GARUDA plays a crucial role in preserving natural habitats and improving ecosystem health.

# Workflow Diagram
```mermaid
workflowDiagram
    title GARUDA Workflow
    section Initialization
      A[Power On] --> B[Check Power Supply]
      B --> C[Initialize Rover & Drone]
    section Monitoring
      D[Start Monitoring] --> E[Determine Monitoring Type]
      E --> F[Fire Detection]
      E --> G[Water Safety]
      E --> H[Illegal Logging]
      E --> I[Litter Cleanup]
      E --> J[Wildlife Protection]
    section Action
      F --> K[Drone: Fire Sensor Activation]
      G --> L[Rover: Monitor Water Quality]
      H --> M[Drone: Camera & Sensors for Logging]
      I --> N[Rover: Detect and Collect Litter]
      J --> O[Infrared Detection for Injured Animals]
    section Data Transmission
      K --> P[Send Data to Ground Station]
      L --> P
      M --> P
      N --> P
      O --> P
    section Real-time Response
      P --> Q[Real-time Data Analysis]
      Q --> R[Immediate Action by Authorities]
      R --> S[Report Completed]

# Concept Map 
```mermaid
graph LR
    A[Project GARUDA] --> B[Rover]
    A --> C[Drone]
    B --> D[Arduino Mega]
    B --> E[GPS]
    B --> F[Ultrasonic Sensors]
    B --> G[10kg Torque Gear Motor]
    B --> H[Infrared & Normal Cameras]
    B --> I[Temperature & Humidity Sensors]
    B --> J[Servo Motor (Crane)]
    B --> K[Hydraulic Motor (Doors)]
    B --> L[NRF24L01 (Manual Control)]
    C --> M[PIXHAWK (Flight Controller)]
    C --> N[Telemetry (Data Transmission)]
    C --> O[Infrared & Night Vision Cameras]
    C --> P[Fire Sensor]
    C --> L
    B --> Q[Solar Panel (Primary Power)]
    B --> R[Battery (Backup Power)]
    A --> S[Wildlife Protection]
    A --> T[Environmental Monitoring]
    T --> U[Water Safety]
    T --> V[Illegal Logging]
    T --> W[Litter Cleanup]
    T --> X[Fire Detection]
    S --> Y[Injured Animal Detection]
    Y --> Z[Authorities Alerted]
    A --> AA[Real-time Monitoring]

# TECH STACK
## Rover
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
## Drone
- **Flight Controller:** PIXHAWK (brain of the drone, pre-programmed and manual control)
- **Telemetry:** Data transmission from drone to ground station
- **Surveillance:** Infrared and night vision cameras (for identifying living vs. non-living objects)
- **Fire Detection:** Fire sensor (for early fire detection)
- **Manual Control:** Remote control option for manual operation

# NOVELITY
- **Dual-system operation:** The rover and drone work together, providing ground and aerial monitoring capabilities.
- **Autonomous and manual control:** The rover and drone can operate autonomously or be manually controlled, enhancing flexibility.
- **Comprehensive sensor suite:** GARUDA uses GPS, ultrasonic sensors, infrared cameras, fire sensors, and environmental monitors (temperature, humidity) for a wide range of applications.
- **Energy efficiency:** Powered primarily by solar energy with battery backup, ensuring sustainability for long-duration missions.
- **Wildlife protection:** It can detect injured animals and alert authorities, contributing directly to wildlife conservation efforts.

# SOLUTION 
- **Fire Detection:** The drone detects fires early, alerting authorities to prevent wildfires.
- **Water Safety:** Monitors water bodies for pollution and unsafe conditions.
- **Illegal Logging:** Uses cameras and sensors to detect illegal logging activities.
- **Litter Cleanup:** Detects and assists in removing litter from remote areas.
- **Wildlife Injury Detection:** Identifies injured animals using infrared and night vision, alerting officials for rescue.
- **Sustainable Operation:** Powered by solar energy with battery backup for long-term, eco-friendly use.
- **Real-time Monitoring:** Transmits data to a central station for immediate action and decision-making.


