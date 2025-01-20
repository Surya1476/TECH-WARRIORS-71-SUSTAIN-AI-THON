# Project GARUDA

## Brief Introduction

GARUDA is an advanced environmental monitoring system combining a rover and drone equipped with sensors to protect ecosystems and wildlife. It provides real-time data on fire detection, water safety, illegal logging, litter cleanup, and wildlife injury detection. Powered by solar energy with backup battery support, GARUDA operates autonomously or via remote control, ensuring sustainability and flexibility. By alerting authorities and contributing to conservation efforts, GARUDA plays a crucial role in preserving natural habitats and improving ecosystem health.

---

## Concept Map

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
