#include <WiFi.h>

const char *ssid = "ESP32-Access-Point";
const char *password = "12345678";



WiFiServer server(1234);
WiFiClient client;

const int buzzerPin = 10; // GPIO10: Low-level triggered buzzer
bool buzzerOn = false;
unsigned long lastMessageTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH); // Turn buzzer OFF initially (HIGH = OFF for low-triggered)

  // Start Soft AP
  WiFi.mode(WIFI_AP);         // Add this
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP: ");
  Serial.println(IP);

  server.begin();
}

void loop() {
  // Accept a new client if current one is disconnected
  if (!client || !client.connected()) {
    client = server.available();
  }

  

  // If data is available from the client
  if (client && client.connected() && client.available()) {
    char received = client.read(); // Read a single byte
    Serial.print("Received: ");
    Serial.println(received);

    if (received == '0') {
      buzzerOn = true;
    } else if (received == '1') {
      buzzerOn = false;
    }

    lastMessageTime = millis();
  }

  // If no message received in 1 sec, turn buzzer off
  if (millis() - lastMessageTime > 1000) {
    buzzerOn = false;
  }

  // Update buzzer state
  digitalWrite(buzzerPin, buzzerOn ? LOW : HIGH); // LOW = ON
}
