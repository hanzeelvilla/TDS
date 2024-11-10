#ifndef TDS_H
#define TDS_H

#include "Arduino.h"

class TDS {
  int pin;
  float volts;
  int samples;

  public:
    TDS(int pinTDS, float voltsTDS = 5.5, int samplesTDS = 30) {
      pin = pinTDS;
      volts = voltsTDS;
      samples = samplesTDS;
    }

    void info();
}

#endif TDS_H