
#include <RF24.h>
#include <BTLE.h>

#define CE_pin 7
#define CSN_pin 8

//====# pre initializing #====
RF24 radio(CE_pin,CSN_pin);
BTLE btle(&radio);

void initBT(){
  btle.begin("S01");
}

struct my_service_data {
  int16_t service_uuid;
  uint16_t temp;
  uint16_t humidity;
  uint16_t pressure;
  uint16_t voltage;
};

void testBT(){
  my_service_data buf;
  buf.service_uuid = NRF_TEMPERATURE_SERVICE_UUID;
  buf.temp = (uint16_t) ((data.temp * 100) + 10000);
  buf.humidity = (uint16_t) (data.humidity * 100);
  buf.pressure = (uint16_t) ((data.pressure * 100) - 70000);
  buf.voltage = (uint16_t) (data.voltageInternal);

  if (DEBUG) {
    Serial.println("Sending data");
    Serial.print ("Pressure: ");
    Serial.println(buf.pressure);
    Serial.print ("Humidity: ");
    Serial.println(buf.humidity);
    Serial.print ("Temperature: ");
    Serial.println(buf.temp);
    Serial.print ("Voltage: ");
    Serial.println(buf.voltage);
  }

  for (int k; k<3; k++) {
    if(!btle.advertise(&buf, sizeof(buf))) {
      Serial.println("BTLE advertisement failure");
    }
    btle.hopChannel();
  }
  
  if (DEBUG){
    Serial.print(sizeof(buf));
    Serial.println(" bytes sent");
    Serial.println("");
  }
}

