#include <WiFi.h>
#include <WebServer.h>

// Defina SSID e senha da rede Wi-Fi (AP)
const char* ssid = "ESP32_HK_LAB";
const char* password = "passwd123";

// Cria servidor web na porta 80
WebServer server(80);

void handleRoot() {
  String ip = WiFi.softAPIP().toString();
  String mac = WiFi.softAPmacAddress();

  String page = "<!DOCTYPE html><html><head><title>Intro M5StickC</title></head><body>";
  page += "<h1>Bem-vindo ao M5StickC Hacking Lab</h1>";
  page += "<p><b>IP:</b> " + ip + "</p>";
  page += "<p><b>MAC:</b> " + mac + "</p>";
  page += "<p><b>SSID:</b> " + String(ssid) + "</p>";
  page += "<p><b>Senha:</b> " + String(password) + "</p>";
  page += "</body></html>";

  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  // Inicializa modo AP (Access Point)
  WiFi.softAP(ssid, password);

  Serial.println("Access Point criado");
  Serial.print("SSID: "); Serial.println(ssid);
  Serial.print("Senha: "); Serial.println(password);
  Serial.print("IP do AP: "); Serial.println(WiFi.softAPIP());

  // Configura rota para página web
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
