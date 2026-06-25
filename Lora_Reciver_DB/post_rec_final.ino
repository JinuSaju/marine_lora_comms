#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <HTTPClient.h>

// LoRa pins
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_CS    5
#define LORA_RST   14
#define LORA_DIO0  2

const char* ssid = "Sabarii";
const char* password = "ummaaaaa";
const char* serverUrl = "http://10.17.121.208:3000/api/data";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("LoRa Receiver Starting...");

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);

  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);

  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


  if (!LoRa.begin(866E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  LoRa.setSpreadingFactor(9);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);

  Serial.println("LoRa Receiver Ready...");
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    String received = "";

    while (LoRa.available()) {
      received += (char)LoRa.read();
    }

    Serial.println("----- RECEIVED -----");
    Serial.print("Message: ");
    Serial.println(received);

    Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi());

    Serial.print("SNR: ");
    Serial.println(LoRa.packetSnr());

    Serial.println("--------------------");
    int comma = received.indexOf(',');

    String latitude = received.substring(0, comma);
    String longitude = received.substring(comma + 1);

    WiFiClient client;
    HTTPClient http;

    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"latitude\":" + latitude + ",";
    json += "\"longitude\":" + longitude;
    json += "}";

    int code = http.POST(json);

    Serial.print("POST Code: ");
    Serial.println(code);

    http.end();
  }
}