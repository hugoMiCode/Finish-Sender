#ifndef WIFI_RECEIVER_H
#define WIFI_RECEIVER_H

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>


class WiFiReceiver {
private:
  RF24 radio;
  const byte address[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x01};

public:
  WiFiReceiver(uint8_t cePin, uint8_t csnPin) : radio(cePin, csnPin) {}

  void setup() {
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
  }

  bool available() {
    return radio.available();
  }

  String readMessage() { 
    char message[32];
    radio.read(&message, sizeof(message));
    
    return message;
  }
};

#endif // WIFI_RECEIVER_H
