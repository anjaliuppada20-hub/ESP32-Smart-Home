#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// GPIO pins
const int LIGHT_PIN = 2;
const int FAN_PIN = 4;

WebServer server(80);

// Create smart-home web page
String webPage() {
  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<title>ESP32 Smart Home</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "</head>";

  html += "<body style='text-align:center; font-family:Arial;'>";
  html += "<h1>ESP32 Smart Home</h1>";

  html += "<h2>Light</h2>";
  html += "<a href='/light/on'>";
  html += "<button style='font-size:22px;'>LIGHT ON</button>";
  html += "</a> ";

  html += "<a href='/light/off'>";
  html += "<button style='font-size:22px;'>LIGHT OFF</button>";
  html += "</a>";

  html += "<h2>Fan</h2>";
  html += "<a href='/fan/on'>";
  html += "<button style='font-size:22px;'>FAN ON</button>";
  html += "</a> ";

  html += "<a href='/fan/off'>";
  html += "<button style='font-size:22px;'>FAN OFF</button>";
  html += "</a>";

  html += "</body>";
  html += "</html>";

  return html;
}

// Home page
void handleRoot() {
  server.send(200, "text/html", webPage());
}

// Light control
void lightOn() {
  digitalWrite(LIGHT_PIN, HIGH);
  server.send(200, "text/html", webPage());
}

void lightOff() {
  digitalWrite(LIGHT_PIN, LOW);
  server.send(200, "text/html", webPage());
}

// Fan control
void fanOn() {
  digitalWrite(FAN_PIN, HIGH);
  server.send(200, "text/html", webPage());
}

void fanOff() {
  digitalWrite(FAN_PIN, LOW);
  server.send(200, "text/html", webPage());
}

void setup() {
  Serial.begin(115200);

  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");

  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Web server routes
  server.on("/", handleRoot);

  server.on("/light/on", lightOn);
  server.on("/light/off", lightOff);

  server.on("/fan/on", fanOn);
  server.on("/fan/off", fanOff);

  server.begin();

  Serial.println("Smart Home Web Server Started");
}

void loop() {
  server.handleClient();
}
