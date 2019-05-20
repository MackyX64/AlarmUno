// Subroutines for use with Alarm_ExtSpkr.ino ONLY!
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
btn_sta_1 = digitalRead(btn_pin_1);
  if (btn_sta_1==false){
    flagAlarm=false;
    flagArmed=false;
    MFS.writeLeds(LED_1 | LED_2, OFF);
    ArmedCheck(flagArmed);
  }
}
void AlarmSounder(){
  while(flagAlarm==true){
    tone(spk_pin_1,1000);
    DisarmCheck();
    delay(250);
    noTone(spk_pin_1);
  }
}
void CheckTrigger(){
  btn_sta_3 = digitalRead(btn_pin_3);
  if (btn_sta_3==false){
    flagAlarm = !flagAlarm;
    MFS.write("TRIG");
    MFS.writeLeds(LED_2, ON);
    AlarmSounder();    
  }
}
