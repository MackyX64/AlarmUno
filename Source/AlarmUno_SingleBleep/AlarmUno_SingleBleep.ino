// Arduino IDE Libraries
#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
// Local Header Files
#include "MFS_Config.h"
#include "AlarmSubroutines.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  PinSetup_init(); Serial.println("Initializing Board Pins");
  MFShield_init();Serial.println("Initializing MFShield");
}
void loop() {
  // put your main code here, to run repeatedly:
  ArmedCheck(flagArmed);
  
  btn_sta_1 = digitalRead(btn_pin_1);
  if (btn_sta_1==false){
    flagArmed = !flagArmed;
    if (flagAlarm==true){ //Checks if flagAlarm is true
      flagAlarm=false;
      //If true, sets to false so alarm won't sound 
      //after disarming & rearming.
    }
    flagState = !flagState;
    while(digitalRead(btn_pin_1)){
      //Do nothing until button goes HIGH.
    }
  delay(250); //debounce
  }
  if (flagArmed==true){
    CheckTrigger();
  }
}
