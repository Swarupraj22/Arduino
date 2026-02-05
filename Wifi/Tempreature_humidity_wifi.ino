#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

/* -------- DHT CONFIG -------- */
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/* -------- WIFI CONFIG -------- */
const char* ssid     = "Smriti_Pandey";
const char* password = "HelloYar.";

/* -------- WEB SERVER -------- */
WebServer server(80);

void handleRoot() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  if (isnan(humidity) || isnan(temperature)) {
    server.send(500, "text/plain", "DHT11 read failed");
    return;
  }

  String html = "<!DOCTYPE html><html>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<meta http-equiv='refresh' content='2'>";

  // Font Awesome Icons
  html += "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.1/css/all.min.css'>";

  html += "<style>";
  html += "body{font-family:Arial;background:#eef2f3;text-align:center;margin:0;padding:0;}";
  html += "h1{background:#2c3e50;color:white;padding:15px;margin:0;}";
  html += ".card{background:white;margin:20px;padding:20px;border-radius:12px;";
  html += "box-shadow:0 6px 12px rgba(0,0,0,0.15);}";
  html += ".icon{font-size:50px;color:#3498db;margin-bottom:10px;}";
  html += ".value{font-size:32px;font-weight:bold;}";
  html += "</style>";

  html += "</head><body>";

  html += "<h1>ESP32 DHT11 Monitor</h1>";

  html += "<div class='card'>";
  html += "<div class='icon'><i class='fa-solid fa-temperature-half'></i></div>";
  html += "<div class='value'>" + String(temperature) + " &deg;C</div>";
  html += "<div>Temperature</div>";
  html += "</div>";

  html += "<div class='card'>";
  html += "<div class='icon'><i class='fa-solid fa-droplet'></i></div>";
  html += "<div class='value'>" + String(humidity) + " %</div>";
  html += "<div>Humidity</div>";
  html += "</div>";

  html += "</body></html>";

  server.send(200, "text/html; charset=UTF-8", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}