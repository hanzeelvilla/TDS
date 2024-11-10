#ifndef TDS_H
#define TDS_H

#define SAMPLES 30

#include <Arduino.h>


class TDS {
  // constructor variables
  int pin;
  float volts;
  // reading variables
  int analogBuffer[SAMPLES];     
  int analogBufferTemp[SAMPLES];
  int analogBufferIndex = 0;
  int copyIndex = 0;

  public:
    TDS(int pinTDS, float voltsTDS = 5.5) {
      pin = pinTDS;
      volts = voltsTDS;
    }

    void info();
};

#endif