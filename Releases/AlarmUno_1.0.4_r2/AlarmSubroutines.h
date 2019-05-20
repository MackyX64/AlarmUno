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
  //Checks button S1 first to see if pressed.
  btn_sta_1 = digitalRead(btn_pin_1);
  if (btn_sta_1==false){
    flagAlarm=false;
    flagArmed=false;
    MFS.writeLeds(LED_1 | LED_2, OFF);
    ArmedCheck(flagArmed);
    Serial.println("Alarm Reset and Disarmed.");
  }
  //Checks Serial Buffer to see if command is entered.
  String input = "";
  while (Serial.available() > 0){
    input += (char) Serial.read(); 
    //^ This line parses the input as a variable to be used in command execution.
    delay(5); //Delay for 5 ms so next character has time to be received.
  }
  input.trim(); //Forcefully removes /n if Serial Input contains newline.
  if (input=="DISARM"||input=="disarm"){
    flagAlarm=false;
    flagArmed=false;
    MFS.writeLeds(LED_1 | LED_2, OFF);
    ArmedCheck(flagArmed);
    Serial.println("Alarm Disarmed and Reset.");
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
