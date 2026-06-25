#include <WiFi.h>
#include <WebServer.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <LoRa.h>

// ---------- LoRa Pins ----------
#define LORA_SCK  18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_CS   5
#define LORA_RST  14
#define LORA_DIO0 2

// ---------- GPS ----------
HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

// ---------- WiFi ----------
const char* ssid = "Galaxy_S24";
const char* password = "123456789";

WebServer server(80);

// ---------- Variables ----------
String latitude = "Waiting...";
String longitude = "Waiting...";
String statusMsg = "Starting...";

int sats = 0;
unsigned long charsCount = 0;

// ---------- Web Page ----------
void handleRoot() {
  String page = "<html><head><meta http-equiv='refresh' content='1'>";
  page += "<style>body{font-family:Arial;text-align:center;margin-top:50px;}h2{color:blue;}</style>";
  page += "</head><body>";

  page += "<h2>ESP32 GPS LoRa Monitor</h2>";
  page += "<p><b>Sats:</b> " + String(sats) + " | <b>Chars:</b> " + String(charsCount) + "</p>";
  page += "<p><b>Latitude:</b> " + latitude + "</p>";
  page += "<p><b>Longitude:</b> " + longitude + "</p>";
  page += "<p><b>Status:</b> " + statusMsg + "</p>";

  page += "</body></html>";

  server.send(200, "text/html", page);
}

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);

  // WiFi
  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();

  // LoRa
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(866E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  LoRa.setSpreadingFactor(9);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);

  Serial.println("Node A Ready");
}

// ---------- Loop ----------
void loop() {
  server.handleClient();

  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  sats = gps.satellites.value();
  charsCount = gps.charsProcessed();

  if (gps.location.isValid()) {
    latitude = String(gps.location.lat(), 6);
    longitude = String(gps.location.lng(), 6);
    statusMsg = "GPS Fixed";

    String packet = latitude + "," + longitude;

    LoRa.beginPacket();
    LoRa.print(packet);
    LoRa.endPacket();
  } 
  else {
    latitude = "Waiting...";
    longitude = "Waiting...";
    statusMsg = "Searching...";
  }

  Serial.print("Sats: ");
  Serial.print(sats);
  Serial.print(" | Chars: ");
  Serial.print(charsCount);
  Serial.print(" | Latitude: ");
  Serial.print(latitude);
  Serial.print(" Longitude: ");
  Serial.print(longitude);
  Serial.print(" Status: ");
  Serial.println(statusMsg);

  delay(1000);
}