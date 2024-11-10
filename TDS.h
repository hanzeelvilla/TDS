#ifndef TDS_H
#define TDS_H

#define SAMPLES 30
#define SAMPLES_DELAY 40U
#define LATEST_SAMPLES_DELAY 800U

#include <Arduino.h>

struct TDSData {
  float averageVoltage;
  float compensationCoefficient;
  float compensationVoltage;
  int ppm;
};

class TDS {
  int pin;
  float volts;

  int getMedianNum(int bArray[], int iFilterLen);

  public:
    TDS(int pinTDS, float voltsTDS = 5.5) {
      pin = pinTDS;
      volts = voltsTDS;
    }

    void init();
    void info();
    TDSData read(float temperature = 25);
};

#endif