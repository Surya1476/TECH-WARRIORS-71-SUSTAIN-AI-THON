#include <SPI.h>
#include <RF24.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <DHT.h>
#include <Servo.h> // Include the Servo library

// RF24 setup
RF24 radio(9, 10);              // CE, CSN pins for nRF24L01
const byte address[6] = "00001"; // Unique address for pairing

// DHT Sensor setup
#define DHTPIN 4         // Pin where the DHT sensor is connected
#define DHTTYPE DHT11    // DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

// Motor control pins
const int motor1Forward = 2;
const int motor1Backward = 3;
const int motor2Forward = 4;
const int motor2Backward = 5;

// Ultrasonic sensor pins
const int trigFront = 6;
const int echoFront = 7;
const int trigRight = 8;
const int echoRight = 9;
const int trigLeft = 12;
const int echoLeft = 13;
const int trigBack = 14;
const int echoBack = 15;

// GPS setup and dynamic waypoint data
SoftwareSerial gpsSerial(11, 10); // RX, TX for GPS
TinyGPSPlus gps;

// Servo setup
Servo servo1; // Base rotation
Servo servo2; // Shoulder lift
Servo servo3; // Elbow flex
Servo servo4; // Wrist rotation

// Initialize servo pins
const int servo1Pin = 15; // Pin for servo 1
const int servo2Pin = 16; // Pin for servo 2
const int servo3Pin = 17; // Pin for servo 3
const int servo4Pin = 18; // Pin for servo 4

struct Waypoint {
    float latitude;
    float longitude;
};

Waypoint waypoints[10]; // Array to store waypoints (up to 10)
int currentWaypoint = 0;
int totalWaypoints = 0;

// PWM channels for manual control
int ch1_pin = A0; // Steering (update as necessary)
int ch2_pin = A1; // Throttle (update as necessary)

void setup() {
    Serial.begin(9600);
    gpsSerial.begin(9600);
    
    dht.begin(); // Initialize the DHT sensor

    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();

    // Initialize servos
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);
    servo3.attach(servo3Pin);
    servo4.attach(servo4Pin);

    pinMode(motor1Forward, OUTPUT);
    pinMode(motor1Backward, OUTPUT);
    pinMode(motor2Forward, OUTPUT);
    pinMode(motor2Backward, OUTPUT);

    pinMode(trigFront, OUTPUT);
    pinMode(echoFront, INPUT);
    pinMode(trigRight, OUTPUT);
    pinMode(echoRight, INPUT);
    pinMode(trigLeft, OUTPUT);
    pinMode(echoLeft, INPUT);
    pinMode(trigBack, OUTPUT);
    pinMode(echoBack, INPUT);

    pinMode(ch1_pin, INPUT);
    pinMode(ch2_pin, INPUT);

    randomSeed(analogRead(0)); // Initialize randomness
}

void loop() {
    // Check if RF data is available
    if (radio.available()) {
        char locationData[32] = ""; // Buffer for received data
        radio.read(&locationData, sizeof(locationData)); // Read data
        Serial.print("Received GPS Data: ");
        Serial.println(locationData);

        // Parse `locationData` as "lat,lon" and add it to waypoints
        float lat, lon;
        if (sscanf(locationData, "%f,%f", &lat, &lon) == 2) {
            if (totalWaypoints < 10) {
                waypoints[totalWaypoints++] = {lat, lon};
                Serial.print("Waypoint added: ");
                Serial.print(lat, 6);
                Serial.print(", ");
                Serial.println(lon, 6);
            } else {
                Serial.println("Waypoint storage full.");
            }
        }
    }

    // Read temperature and humidity
    float temperature = dht.readTemperature(); // Read temperature in Celsius
    float humidity = dht.readHumidity();       // Read humidity

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
    } else {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C, Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }

    if (gpsSerial.available() > 0) {
        Serial.println("Auto Mode");
        while (gpsSerial.available() > 0) {
            gps.encode(gpsSerial.read());
        }

        if (gps.location.isValid()) {
            float currentLat = gps.location.lat();
            float currentLon = gps.location.lng();

            float frontDistance = readUltrasonic(trigFront, echoFront);
            float rightDistance = readUltrasonic(trigRight, echoRight);
            float leftDistance = readUltrasonic(trigLeft, echoLeft);
            float backDistance = readUltrasonic(trigBack, echoBack);

            if (frontDistance < 50 || rightDistance < 50 || leftDistance < 50 || backDistance < 50) {
                randomMovement();
                Serial.println("Obstacle detected!");
                delay(1000);
            } else {
                if (currentWaypoint < totalWaypoints) {
                    moveToWaypoint(waypoints[currentWaypoint], currentLat, currentLon);
                } else {
                    stopMotors();
                    Serial.println("All waypoints reached.");
                }
            }
        } else {
            Serial.println("Waiting for valid GPS data...");
        }
    } else {
        Serial.println("Manual Mode");
        int ch1_val = pulseIn(ch1_pin, HIGH);
        int ch2_val = pulseIn(ch2_pin, HIGH);
        int throttle = map(ch2_val, 1000, 2000, -255, 255);
        int steering = map(ch1_val, 1000, 2000, -255, 255);
        controlMotors(throttle, steering);
        delay(10);
    }
}

void controlMotors(int throttle, int steering) {
    int leftMotorSpeed = constrain(throttle + steering, -255, 255);
    int rightMotorSpeed = constrain(throttle - steering, -255, 255);

    if (leftMotorSpeed > 0) moveLeft();
    else if (leftMotorSpeed < 0) moveRight();

    if (rightMotorSpeed > 0) moveForward();
    else if (rightMotorSpeed < 0) moveBack();
}

float readUltrasonic(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    return duration * 0.034 / 2;
}

void moveToWaypoint(Waypoint target, float currentLat, float currentLon) {
    float distance = calculateDistance(currentLat, currentLon, target.latitude, target.longitude);
    Serial.print("Distance to waypoint: ");
    Serial.println(distance);

    if (distance < 5.0) {
        Serial.print("Reached waypoint: ");
        Serial.println(currentWaypoint);
        currentWaypoint++;
        stopMotors();
        delay(2000);
    } else {
        Serial.print("Moving to waypoint: ");
        Serial.print(target.latitude, 6);
        Serial.print(", ");
        Serial.println(target.longitude, 6);
        moveForward();
    }
}

float calculateDistance(float lat1, float lon1, float lat2, float lon2) {
    const float R = 6371000; // Earth radius in meters
    float phi1 = lat1 * (PI / 180);
    float phi2 = lat2 * (PI / 180);
    float deltaPhi = (lat2 - lat1) * (PI / 180);
    float deltaLambda = (lon2 - lon1) * (PI / 180);

    float a = sin(deltaPhi / 2) * sin(deltaPhi / 2) +
              cos(phi1) * cos(phi2) *
              sin(deltaLambda / 2) * sin(deltaLambda / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c; // Distance in meters
}

void randomMovement() {
    switch (random(0, 4)) {
        case 0: stopMotors(); break;
        case 1: moveRight(); break;
        case 2: moveLeft(); break;
        case 3: moveBack(); break;
    }
}

void moveForward() {
    digitalWrite(motor1Forward, HIGH);
    digitalWrite(motor1Backward, LOW);
    digitalWrite(motor2Forward, HIGH);
    digitalWrite(motor2Backward, LOW);
}

void moveRight() {
    digitalWrite(motor1Forward, HIGH);
    digitalWrite(motor1Backward, LOW);
    digitalWrite(motor2Forward, LOW);
    digitalWrite(motor2Backward, HIGH);
}

void moveLeft() {
    digitalWrite(motor1Forward, LOW);
    digitalWrite(motor1Backward, HIGH);
    digitalWrite(motor2Forward, HIGH);
    digitalWrite(motor2Backward, LOW);
}

void moveBack() {
    digitalWrite(motor1Forward, LOW);
    digitalWrite(motor1Backward, HIGH);
    digitalWrite(motor2Forward, LOW);
    digitalWrite(motor2Backward, HIGH);
}

void stopMotors() {
    digitalWrite(motor1Forward, LOW);
    digitalWrite(motor1Backward, LOW);
    digitalWrite(motor2Forward, LOW);
    digitalWrite(motor2Backward, LOW);
}

// Function to control the servo arm
void controlServoArm(int servo1Pos, int servo2Pos, int servo3Pos, int servo4Pos) {
    servo1.write(servo1Pos);
    servo2.write(servo2Pos);
    servo3.write(servo3Pos);
    servo4.write(servo4Pos);
}

// Example usage of controlServoArm
void useServoArm() {
    controlServoArm(90, 45, 90, 90); // Example positions
}
