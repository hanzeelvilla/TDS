#include "TDS.h"

TDS tds(27, 3.3);

void setup() {
  Serial.begin(115200);
  tds.info();
}

void loop() {
  int tdsValue = tds.read();
  Serial.print("TDS Value:");
  Serial.print(tdsValue);
  Serial.println("ppm");
}