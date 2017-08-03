
#include "SparkFunBME280.h"
#include "Wire.h"


BME280 bme;

void initializeBME() {

  bme.settings.commInterface = I2C_MODE;
  bme.settings.I2CAddress = 0x76;
  bme.settings.runMode = 1; //3 - normal, 1 -?
  bme.settings.tStandby = 0;
  bme.settings.filter = 0;
  bme.settings.tempOverSample = 1;
  bme.settings.pressOverSample = 1;
  bme.settings.humidOverSample = 1;

  bme.begin();

  //BME280 requires about 2 ms to start up.
  delay(5);
}

void readMeasurementFromBME() {
  data.temp = bme.readTempC(); //celsius
  data.pressure = bme.readFloatPressure() / 100; //hPa
  data.humidity = bme.readFloatHumidity(); //%

  if (DEBUG) {
    Serial.println("BME data: ");
    Serial.print("Temperature: ");
    Serial.println(data.temp);
    Serial.print("Pressure: ");
    Serial.println(data.pressure);
    Serial.print("Humidity: ");
    Serial.println(data.humidity);
    Serial.println("");
  }
}

void bmeForceRead() {

    // We set the sensor in "forced mode" to force a reading.
    // After the reading the sensor will go back to sleep mode.
    uint8_t value = bme.readRegister(BME280_CTRL_MEAS_REG);
    value = (value & 0xFC) + 0x01;
    bme.writeRegister(BME280_CTRL_MEAS_REG, value);

    // Measurement Time (as per BME280 datasheet section 9.1)
    // T_max(ms) = 1.25
    //  + (2.3 * T_oversampling)
    //  + (2.3 * P_oversampling + 0.575)
    //  + (2.4 * H_oversampling + 0.575)
    //  ~ 9.3ms for current settings
    delay(10);

}
