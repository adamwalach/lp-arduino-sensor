
struct MeasurementData {
    float temp;
    float humidity;
    float pressure;
    long voltageInternal;
    //long voltageExternal;
    long tempinternal;
};

MeasurementData data = {0.0, 0.0, 0.0, 0, 0};

void readData(){
   data.voltageInternal = readVcc();
   data.tempinternal = readInternalTemp();
   //data.voltageExternal = readExternalVoltage(data.voltageInternal);

   if (DEBUG){
     Serial.print("Vcc: ");
     Serial.println( data.voltageInternal, DEC ); 
     //Serial.print("Battery: ");
     //Serial.println( data.voltageExternal, DEC ); 
     Serial.print("Temp: ");
     Serial.println( data.tempinternal, DEC );
   }
   
   bmeForceRead();
   readMeasurementFromBME();  
}

