#include <SPI.h>
#include <RF24.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

RF24 radio(9, 10);            // CE, CSN pins for nRF24L01
const byte address[6] = "00001"; // Unique address for pairing

TinyGPSPlus gps;              // GPS object
SoftwareSerial ss(4, 3);      // RX, TX for GPS module

const int fireSensorPin = 2;  // Digital pin connected to fire sensor's DO
bool fireDetected = false;    // State variable for fire detection

void setup() {
  Serial.begin(9600);
  ss.begin(9600);             // GPS module baud rate
  pinMode(fireSensorPin, INPUT); // Set fire sensor pin as input

  radio.begin();
  radio.openWritingPipe(address); // Set address for communication
  radio.setPALevel(RF24_PA_MIN);  // Power level to minimum
  radio.stopListening();          // Set as transmitter
}

void loop() {
  // Check if fire sensor detects fire
  fireDetected = digitalRead(fireSensorPin);

  if (fireDetected) {
    // Process GPS data if fire is detected
    while (ss.available() > 0) {   // Check if GPS data is available
      gps.encode(ss.read());       // Parse GPS data
    }

    if (gps.location.isUpdated()) {  // If location is updated
      float latitude = gps.location.lat();
      float longitude = gps.location.lng();

      // Format GPS coordinates as a string
      char locationData[32];
      snprintf(locationData, sizeof(locationData), "Lat:%.6f,Lng:%.6f", latitude, longitude);

      // Send the GPS coordinates over nRF24L01
      radio.write(&locationData, sizeof(locationData)); // Send coordinates
      Serial.print("Alert sent with GPS Coordinates: ");
      Serial.println(locationData);
      
      delay(1000); // Send once per second if fire is still detected
    }
  }
}
