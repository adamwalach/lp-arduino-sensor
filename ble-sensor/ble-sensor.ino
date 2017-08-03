  /*
 * https://github.com/floe/BTLE/blob/master/examples/temperature/temperature.ino
 * Emulates a nRF8001 temperature beacon; 
 * reads temperature from a DHT11 and sends it via BTLE.
 * Compatible with Nordic Semiconductor apps such as
 * nRF Master Control Panel or nRF Temp 2.0.
 */

#define DEBUG true

void setup() {
  Serial.begin(115200);
  if (DEBUG){
    Serial.println("\nBTLE temperature sender");
  }
  setAllPinsToLow();
  disableAnalogInputs();
  disableADC();
  initializeBME();
  initBT();
  readData();
}


void loop() {
  unsigned long StartTime = millis();
  delay(2);
  readData();
  testBT();
  if (DEBUG) {
    stopTimer(StartTime);
  }
  powerdown();
}


