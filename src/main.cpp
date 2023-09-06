#include "IRSender.h"
#include "WifiReceiver.h"

#define IR_SENDER_PIN 2
#define WIFI_CE_PIN 7
#define WIFI_CSN_PIN 8


IRSender irSender(IR_SENDER_PIN, Puce::Finish);
WiFiReceiver wifiReceiver(WIFI_CE_PIN, WIFI_CSN_PIN);


void setup() {
  Serial.begin(115200);

  irSender.begin();
  wifiReceiver.setup();
}

void loop() {
  irSender.sendSignal();

  if (wifiReceiver.available()) {
    String message = wifiReceiver.readMessage();

    Serial.print("Message reçu: "); Serial.println(message);
  }
}
