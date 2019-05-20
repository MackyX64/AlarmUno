// Subroutines for use with AlarmUno Programs Only!
void ArmedCheck(bool flagArmed){
  if (flagArmed==true){
    MFS.write("ON  ");
    MFS.writeLeds(LED_1, ON);
  }
  else{
    MFS.write("OFF ");
    MFS.writeLeds(LED_1, OFF);
  }
}
void DisarmCheck(){
  String input = "";
  while (Serial.available() > 0){
    input += (char) Serial.read(); 
    //^ This line parses the input as a variable to be used in command execution.
    delay(5); //Delay for 5 ms so next character has time to be received.
  }
  if (input=="DISARM"){
    flagAlarm=false;
    flagArmed=false;
    Serial.println("Alarm Disarmed and Reset.");
    MFS.writeLeds(LED_1 | LED_2, OFF);
    ArmedCheck(flagArmed);
  }
}

void AlarmSounder(){
  while(flagAlarm==true){
    tone(spk_pin_1, 800, 250); // Uses pin defined for speaker component.
    DisarmCheck();
    delay(250);
    tone(spk_pin_1, 1000, 250); // Uses pin defined for speaker component.
    DisarmCheck();
    delay(250);
  }
}
void CheckTrigger(){
  btn_sta_3 = digitalRead(btn_pin_3);
  if (btn_sta_3==false){
    flagAlarm = !flagAlarm;
    MFS.write("TRIG");
    MFS.writeLeds(LED_2, ON);
    Serial.println("ALARM TRIGGERED! TYPE 'DISARM' TO RESET ALARM!");
    AlarmSounder();    
  }
}
