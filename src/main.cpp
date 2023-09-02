#include "IRSender.h"
#include "WifiReceiver.h"

const int irPin = 2;
const int wifiCePin = 7;
const int wifiCsnPin = 8;


IRSender irSender(irPin);
WiFiReceiver wifiReceiver(wifiCePin, wifiCsnPin);


void setup() {
  Serial.begin(115200);

  irSender.begin();
  wifiReceiver.begin(); // probleme ca empeche de faire fonctionner blink (LED_BUILTIN) => SDK sur le pin 13 = LED_BUILTIN
}

void loop() {
  irSender.sendSignal(1); // Replace with the desired puceId 

  if (wifiReceiver.available()) {
    char message[32] = "";
    wifiReceiver.readMessage(message, sizeof(message));
    Serial.println("Received WiFi message: " + String(message));
  }
}
