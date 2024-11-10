#include <cmath>
#include "TDS.h"

void TDS::init() {
  pinMode(pin, INPUT);
  Serial.println("TDS initialized");
}

void TDS::info() {
  Serial.print("Pin: ");
  Serial.println(pin);
  Serial.print("Volts: ");
  Serial.print(volts);
  Serial.println(" V");
}

TDSData TDS::read(float temperature) {
  static unsigned long analogSampleTimepoint = millis();
  static unsigned long printTimepoint = millis();

  static int analogBuffer[SAMPLES];     
  static int analogBufferTemp[SAMPLES];
  static int analogBufferIndex = 0;
  static float averageVoltage = 0;

  if (millis() - analogSampleTimepoint > SAMPLES_DELAY){     
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(pin);   
    analogBufferIndex++;

    if (analogBufferIndex == SAMPLES){ 
      analogBufferIndex = 0;
    }
  }
  
  if (millis() - printTimepoint > LATEST_SAMPLES_DELAY){
    printTimepoint = millis();

    for (int i = 0; i < SAMPLES; i++){
      analogBufferTemp[i] = analogBuffer[i];
    }

    // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    averageVoltage = getMedianNum(analogBufferTemp, SAMPLES) * volts / 4096.0;
      
    // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0)); 
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);

    // temperature compensation
    float compensationVoltage = averageVoltage / compensationCoefficient;

    // return convert voltage value to tds value
    int ppm = ((133.42 * std::pow(compensationVoltage, 3) - 255.86 * std::pow(compensationVoltage, 2) + 857.39 * compensationVoltage) * 0.5);

    TDSData tds;
    tds.averageVoltage = averageVoltage;
    tds.compensationCoefficient = compensationCoefficient;
    tds.compensationVoltage = compensationVoltage;
    tds.ppm = ppm;

    return tds;
  }   
}

// median filtering algorithm
int TDS::getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];

  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];

  int bTemp;

  for (int i = 0; i < iFilterLen - 1; i++) {
    for (int j = 0; j < iFilterLen - i - 1; j++) {
      if (bTab[j] > bTab[j + 1]) {
        bTemp = bTab[j];
        bTab[j] = bTab[j + 1];
        bTab[j + 1] = bTemp;
      }
    }
  }

  if ((iFilterLen & 1) > 0)
    return bTab[(iFilterLen - 1) / 2];
  else
    return (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
}