
void stopTimer(unsigned long startTime){
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;
  Serial.print("Execution time: ");
  Serial.println(elapsedTime);
  // if cpu is going to sleep after this command serial port may not
  // be fast enough to push data
  delay(10); 
}
