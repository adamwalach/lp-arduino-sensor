#include <SPI.h>
#include <RF24.h>
#include <BTLE.h>

RF24 radio(2,15);

BTLE btle(&radio);

void setup() {

  Serial.begin(115200);
  while (!Serial) { }
  Serial.println("BTLE advertisement receiver");

  btle.begin("");
}

void loop() {
    
  //Serial.print("Listening... ");
  String bname = "";
  if (btle.listen()) {
    if (btle.buffer.payload[5] != 53) {
      Serial.print("Got payload: ");
      for (uint8_t i = 0; i < (btle.buffer.pl_size)-6; i++) { 
        Serial.print(btle.buffer.payload[i],HEX); 
        Serial.print(" ");
      }
      Serial.println("");
      return;
    }
    
    for (uint8_t i = 5; i < (btle.buffer.pl_size)-6; i++) {
      if (btle.buffer.payload[i]==11) break;
      bname += (char)btle.buffer.payload[i];
    }
    Serial.print("\nName: ");
    Serial.println(bname);
    
    
  }
  
  //Serial.println("done.");
  btle.hopChannel();
}
