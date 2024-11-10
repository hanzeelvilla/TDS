#ifndef TDS_H
#define TDS_H

#define SAMPLES 30
#define SAMPLES_DELAY 40U

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

  float averageVoltage = 0;

  int getMedianNum(int bArray[], int iFilterLen);

  public:
    TDS(int pinTDS, float voltsTDS = 5.5) {
      pin = pinTDS;
      volts = voltsTDS;
    }

    void init();
    void info();
    int read(float temperature = 25);
};

#endif