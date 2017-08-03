
#include "LowPower.h"

void powerdown(){
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
}

void setAllPinsToLow() {
  //http://heliosoph.mit-links.info/arduino-powered-by-capacitor-reducing-consumption/
  //it saves about 3mA
  for (int x=0; x<14; x++){
    pinMode(x, OUTPUT);
    digitalWrite(x, LOW); 
  }
}

void disableAnalogInputs() {
  // Disable digital input buffers on all analog input pins
  // by setting bits 0-5 of the DIDR0 register to one.
  DIDR0 = DIDR0 | B00111111;
}

void disableADC(){
  // Disable the ADC by setting the ADEN bit (bit 7)  of the
  // ADCSRA register to zero.
  ADCSRA = ADCSRA & B01111111;

  // Disable the analog comparator by setting the ACD bit
  // (bit 7) of the ACSR register to one.
  ACSR = B10000000;
}

