#include "IRSender.h"
#include "WifiReceiver.h"

#define IR_SENDER_PIN 2
#define WIFI_CE_PIN 7
#define WIFI_CSN_PIN 8


IRSender irSender(IR_SENDER_PIN, 0b00);
WiFiReceiver wifiReceiver(WIFI_CE_PIN, WIFI_CSN_PIN);


void setup() {
  Serial.begin(250000);

  irSender.setup();
  wifiReceiver.setup();
}


void loop() {
  irSender.sendPulseSignal(1500);

  if (wifiReceiver.available()) {
    String message = wifiReceiver.readMessage();

    Serial.print("Message reçu: "); Serial.println(message);
  }
}
