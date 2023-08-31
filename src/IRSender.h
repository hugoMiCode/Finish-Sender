#ifndef IR_SENDER_H
#define IR_SENDER_H
#include <Arduino.h>
#include <Chrono.h>

class IRSender {
    private:
  int irPin;
  Chrono pulseClock;

public:
  IRSender(int pin) : irPin(pin) {}

  void begin() {
    pinMode(irPin, OUTPUT);
  }

  void sendPulse(long microsecs) {
    pulseClock.restart();
    while (!pulseClock.hasPassed(microsecs, false)) {
      digitalWrite(irPin, HIGH);
      delayMicroseconds(9);
      digitalWrite(irPin, LOW);
      delayMicroseconds(9);
    }
  }

  void sendSignal(int puceId) {
    sendPulse(400);

    if (puceId == 1)
      delayMicroseconds(400);
    else if (puceId == 2)
      delayMicroseconds(800);
    else if (puceId == 3) {
      delayMicroseconds(800);
      sendPulse(400);
      delayMicroseconds(400);
    }
  }
};

#endif // IR_SENDER_H