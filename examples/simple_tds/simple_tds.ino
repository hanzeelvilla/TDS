#include <TDS.h>

TDS tds(27, 3.3);

void setup() {
  Serial.begin(115200);
  tds.init();
  tds.info();
}

void loop() {
  TDSData tds_data = tds.read(20); // you can pass the temperature from a sensor

  Serial.print("TDS averageVoltage: ");
  Serial.print(tds_data.averageVoltage);
  Serial.println(" V");

  Serial.print("TDS compensationCoefficient: ");
  Serial.println(tds_data.compensationCoefficient);

  Serial.print("TDS compensationVoltage: ");
  Serial.print(tds_data.compensationVoltage);
  Serial.println(" V");

  Serial.print("TDS Value: ");
  Serial.print(tds_data.ppm);
  Serial.println("ppm");

  delay(200);
}