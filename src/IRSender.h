#ifndef IR_SENDER_H
#define IR_SENDER_H

#include <Arduino.h>
#include <Chrono.h>

#define SIGNAL_HIGH_TIME_MCS 400


enum class Puce{
  None = 0,
  Finish = 1,
  Sector1 = 2,
  Sector2 = 3
};


class IRSender {
private:
  int irPin;
  Puce puceId;
  Chrono pulseClock;

public:
  IRSender(int pin, Puce puce) {
    this->irPin = pin;
    this->puceId = puce;
  }

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


  void sendSignal() {
    sendPulse(SIGNAL_HIGH_TIME_MCS);
    
    switch (puceId)
    {
    case Puce::Finish:
      delayMicroseconds(400);
      break;
    case Puce::Sector1:
      delayMicroseconds(800);
      break;
    case Puce::Sector2:
      delayMicroseconds(800);
      sendPulse(SIGNAL_HIGH_TIME_MCS);
      delayMicroseconds(400);
      break;
    default:
      break;
    }
  }
};

#endif // IR_SENDER_H