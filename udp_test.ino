#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <microDS18B20.h>

#define WIFI_SSID "TP-Link_6221"
#define WIFI_PASS "33692869"
#define UDP_PORT 4210

MicroDS18B20<D4> ds18b20;

// UDP
WiFiUDP UDP;
char packet[255];
char reply[] = "Packet received!";

void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();

  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);
}

void loop() {

  ds18b20.requestTemp();

  float temperature = ds18b20.getTemp();
  char str[64];
  int ret = snprintf(str, sizeof(str), "%.2f", temperature);

  UDP.beginPacket(IPAddress(192, 168, 0, 255), 4210);
  UDP.write(str);
  UDP.endPacket();

  delay(1500);
}
