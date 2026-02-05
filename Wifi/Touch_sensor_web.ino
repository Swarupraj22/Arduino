#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Swarup's_Laptop";
const char* password = "Your device is Hacked";

WebServer server(80);

int touchPin = T0;   // GPIO 4

void handleRoot() {
  int touchValue = touchRead(touchPin);

  String html = "<html><head>";
  html += "<meta http-equiv='refresh' content='1'>";  // auto refresh
  html += "</head><body>";
  html += "<h1>ESP32 Touch Sensor</h1>";
  html += "<h2>Touch Value: " + String(touchValue) + "</h2>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}