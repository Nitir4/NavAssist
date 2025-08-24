import processing.net.*; 

Client espClient;

int port = 1234;             // Match with ESP32 serverPort
String serverIP = "192.168.4.2"; // The ESP32 CLIENT device's IP in AP network
float[][] distances = new float[4][121]; // store distance data per angle

void setup() {
  size(800, 800);
  espClient = new Client(this, serverIP, port);
  println("Connecting to ESP32...");
}

void draw() {
  background(0);
  translate(width/2, height/2);

  stroke(0, 255, 0);
  noFill();
  ellipse(0, 0, 600, 600);
  ellipse(0, 0, 400, 400);
  ellipse(0, 0, 200, 200);

  // Draw radar sweep for each sensor
  for (int i = 0; i < 4; i++) {
    pushMatrix();
    float offsetAngle = radians(i * 90); // sensors at 0°, 90°, 180°, 270°
    stroke(0, 150, 255);
    for (int a = 0; a <= 120; a++) {
      float d = distances[i][a];
      if (d > 0 && d < 300) { // valid reading
        float r = map(d, 0, 300, 0, 300);
        float angle = radians(a - 60) + offsetAngle; // center sweep ±60°
        float x = cos(angle) * r;
        float y = sin(angle) * r;
        stroke(d < 70 ? color(255, 0, 0) : color(0, 255, 0));
        point(x, y);
      }
    }
    popMatrix();
  }

  readIncoming();
}

void readIncoming() {
  while (espClient.available() > 0) {
    String line = espClient.readStringUntil('\n');
    if (line != null) {
      line = trim(line);
      String[] parts = split(line, ',');
      if (parts.length == 3) {
        int sensor = int(parts[0]);
        int angle = int(parts[1]);
        float dist = float(parts[2]);
        if (sensor >= 0 && sensor < 4 && angle >= 0 && angle <= 120) {
          distances[sensor][angle] = dist;
        }
      }
    }
  }
}
