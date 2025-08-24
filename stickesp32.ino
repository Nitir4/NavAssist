#include <ESP32Servo.h>
#include <WiFi.h>

// Servo pins
const int servoPins[4] = {13, 12, 14, 27};
Servo servos[4];

// Ultrasonic pins
const int trigPins[4] = {15, 33, 21, 5};
const int echoPins[4] = {2, 25, 19, 18};

// WiFi Client Setup
const char* ssid = "ESP32-Access-Point";   // Your AP ESP32 SSID
const char* password = "12345678";         // Your AP ESP32 password
const char* serverIP = "192.168.4.1";      // IP of the AP ESP32
const int serverPort = 1234;

WiFiClient client;

// Get one smoothed ultrasonic reading (3 samples)
long getSmoothedDistance(int trigPin, int echoPin) {
  long sum = 0;
  int valid = 0;
  for (int i = 0; i < 3; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH, 30000);
    long d = (duration == 0) ? -1 : duration * 0.034 / 2;

    if (d > 0) {
      sum += d;
      valid++;
    }
    delay(5);
  }
  return (valid > 0) ? sum / valid : -1;
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 4; i++) {
    servos[i].attach(servoPins[i]);
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");

  if (!client.connect(serverIP, serverPort)) {
    Serial.println("Connection to server failed!");
  } else {
    Serial.println("Connected to AP server.");
  }
}

void loop() {
  bool danger = false;

  // Sweep forward
  for (int angle = 0; angle <= 120; angle++) {
    servos[0].write(angle);
    servos[1].write(120 - angle);
    servos[2].write(angle);
    servos[3].write(120 - angle);
    delay(30);

    for (int i = 0; i < 4; i++) {
      long d = getSmoothedDistance(trigPins[i], echoPins[i]);
      Serial.print(i); Serial.print(","); Serial.print(angle); Serial.print(",");
      Serial.println(d);

      if (d > 0 && d < 70) danger = true; // valid + within danger range
    }
  }

  // Sweep backward
  for (int angle = 120; angle >= 0; angle--) {
    servos[0].write(angle);
    servos[1].write(120 - angle);
    servos[2].write(angle);
    servos[3].write(120 - angle);
    delay(30);

    for (int i = 0; i < 4; i++) {
      long d = getSmoothedDistance(trigPins[i], echoPins[i]);
      Serial.print(i); Serial.print(","); Serial.print(angle); Serial.print(",");
      Serial.println(d);

      if (d > 0 && d < 70) danger = true;
    }
  }

  // Send message based on any danger
  if (client.connected()) {
    client.write(danger ? '0' : '1');
    Serial.println(danger ? "Sent: 0 (Danger)" : "Sent: 1 (Safe)");
  } else {
    Serial.println("Client not connected.");
  }

  delay(500); // optional pause between full sweeps
}
