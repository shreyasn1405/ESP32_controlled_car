#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "ESP32-CAR";
const char* password = "12345678";

// Motor control pins
const int IN1 = 22;
const int IN2 = 21;
const int IN3 = 19;
const int IN4 = 18;
const int ENA = 23;
const int ENB = 5;

WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  // Initialize motor control pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Stop motors initially
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  
  // Setup WiFi in AP mode
  WiFi.softAP(ssid, password);
  
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  
  // Setup web server routes
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);
  
  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><body><h1>ESP32 Car Control</h1>";
  html += "<a href=\"/forward\"><button>Forward</button></a><br>";
  html += "<a href=\"/backward\"><button>Backward</button></a><br>";
  html += "<a href=\"/left\"><button>Left</button></a><br>";
  html += "<a href=\"/right\"><button>Right</button></a><br>";
  html += "<a href=\"/stop\"><button>Stop</button></a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  server.send(200, "text/plain", "Moving forward");
}

void handleBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  server.send(200, "text/plain", "Moving backward");
}

void handleLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  server.send(200, "text/plain", "Turning left");
}

void handleRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  server.send(200, "text/plain", "Turning right");
}

void handleStop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  server.send(200, "text/plain", "Stopping");
}




























// // Motor control pins
// const int IN1 = 22;
// const int IN2 = 21;
// const int IN3 = 19;
// const int IN4 = 18;
// const int ENA = 23;
// const int ENB = 5;
