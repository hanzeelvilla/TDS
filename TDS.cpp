#include "TDS.h"

void TDS::init() {
  pinMode(pin, INPUT);
}

void TDS::info() {
  Serial.print("Pin: ");
  Serial.println(pin);
  Serial.print("Volts: ");
  Serial.println(volts);
}

int TDS::read(float temperature) {
  static unsigned long analogSampleTimepoint = millis();

  if (millis() - analogSampleTimepoint > SAMPLES_DELAY){     
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(pin);   
    analogBufferIndex++;

    if (analogBufferIndex == SAMPLES){ 
      analogBufferIndex = 0;
    }
  }
  
  static unsigned long printTimepoint = millis();

  if (millis() - printTimepoint > 800U){
    printTimepoint = millis();

    for (copyIndex = 0; copyIndex < SAMPLES; copyIndex++){
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
      
      // read the analog value more stable by the median filtering algorithm, and convert to voltage value
      averageVoltage = getMedianNum(analogBufferTemp, SAMPLES) * (float)volts / 4096.0;
      
      // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0)); 
      float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);

      // temperature compensation
      float compensationVoltage = averageVoltage / compensationCoefficient;

      // return convert voltage value to tds valu
      return ((133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5);
    }
  }   
}

// median filtering algorithm
int TDS::getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];

  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];

  int i, j, bTemp;

  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }

  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;

  return bTemp;
}