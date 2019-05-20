// Subroutines for use with AlarmUno Programs Only!
void ArmedCheck(bool flagArmed) { //ArmedCheck is used to keep checking alarm armed state when not triggered.
  if (flagArmed==true){
    MFS.write("ON  ");
    MFS.writeLeds(LED_1, ON);
  }
  else{
    MFS.write("OFF ");
    MFS.writeLeds(LED_1, OFF);
  }
}
void DisarmCheck() { // DisarmCheck is used to keep checking for input from user to reset alarm state.
  String input = "";
    while (Serial.available() >0){
      input += (char) Serial.read(); //This line parses the input as a variable to be used in command execution.
      delay(5); //Delay for 5 ms so next character has time to be received.
    }
  if (input=="DISARM") {
    Serial.print(">>");Serial.println(input);
    flagAlarm=false;
    flagArmed=false;
    MFS.writeLeds(LED_1 | LED_2, OFF);
    Serial.println("ALARM RESET");
    ArmedCheck(flagArmed);
  }
}
void AlarmSounder() { // Main alarm sounder subroutine, this defines the sound output of the ext speaker on pin 5.
  while(flagAlarm==true){
    tone(spk_pin_1, 800, 250); // Uses pin defined for external speaker component.
    DisarmCheck();
    delay(250);
    tone(spk_pin_1, 1000, 250); // Uses pin defined for external speaker component.
    DisarmCheck();
    delay(250);
  }
}
void CheckTrigger() {
  btn_sta_3 = digitalRead(btn_pin_3); // btn3 on MFS is used as alarm trigger. This would normally be attached to ext sensor.
  if (btn_sta_3==false){
    flagAlarm=true;
    MFS.write("ALAR"); // Displays the message ALAR on MFS 7 Seg Display to indicate alarm is triggered.
    MFS.writeLeds(LED_2, ON); // Indicates that alarm is triggered.
    Serial.println("ALARM TRIGGERED!");
    Serial.println("Type DISARM to reset alarm!");
    AlarmSounder();    
  }
}
