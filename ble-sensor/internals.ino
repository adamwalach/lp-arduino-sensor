
//https://code.google.com/archive/p/tinkerit/wikis/SecretVoltmeter.wiki
long readVcc() { 
  long result; // Read 1.1V reference against AVcc 
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1); 
  delay(2); // Wait for Vref to settle 
  ADCSRA |= _BV(ADSC); // Convert 
  while (bit_is_set(ADCSRA,ADSC)); 
  result = ADCL; 
  result |= ADCH<<8; 
  result = 1126400L / result; // Back-calculate AVcc in mV 
  return result; 
}

//https://code.google.com/archive/p/tinkerit/wikis/SecretThermometer.wiki
long readInternalTemp() { 
  long result; // Read temperature sensor against 1.1V reference 
  ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3); 
  delay(2); // Wait for Vref to settle 
  ADCSRA |= _BV(ADSC); // Convert 
  while (bit_is_set(ADCSRA,ADSC)); 
  result = ADCL; 
  result |= ADCH<<8;
  result = (result - 125) * 1075;
  return result;
}


// if voltage regulator is used we can measure voltage on its input,
// so we get real value of voltage on battery
long readExternalVoltage(long vccVoltage){
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (vccVoltage/1000.0 / 1023.0);
  return voltage*1000;
}

