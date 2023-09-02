#ifndef IR_SENDER_H
#define IR_SENDER_H

#include <Arduino.h>
#include <Chrono.h>

#define SIGNAL_HIGH_TIME_MCS 400

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
    sendPulse(SIGNAL_HIGH_TIME_MCS);

    
    if (puceId == 1)
      delayMicroseconds(400);
    else if (puceId == 2)
      delayMicroseconds(800);
    else if (puceId == 3) {
      delayMicroseconds(800);
      sendPulse(SIGNAL_HIGH_TIME_MCS);
      delayMicroseconds(400);
    }
  }
};

#endif // IR_SENDER_H