#include "TDS.h"

void TDS::info() {
  Serial.print("Pin: ");
  Serial.println(pin);
  Serial.print("Volts: ");
  Serial.println(volts);
  Serial.print("Samples: ");
  Serial.println(samples);
}