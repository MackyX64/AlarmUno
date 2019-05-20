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
  Serial.println("Initialisation Complete! Starting Program...");
  delay(500);
  while (!Serial);
  Serial.println("ALARM PROGRAM READY!");
  Serial.println("COMMANDS: ARM - Arms alarm, DISARM - Disarms alarm.");
}
void loop() {
  // put your main code here, to run repeatedly:
  ArmedCheck(flagArmed); // Checks if alarm is armed.
  if (Serial.available()){//Enables keyboard input. (input will accept any value)
    //Used here so the user can tell the program which pin the subroutine should use.
    String input = "";
    while (Serial.available() >0){
      input += (char) Serial.read(); //This line parses the input as a variable to be used in command execution.
      delay(5); //Delay for 5 ms so next character has time to be received.
    }
    Serial.println(input);
    if (input=="ARM"){
      //goto ALARM_ARM;
      flagArmed=true;
      Serial.println("flagArmed.setState(TRUE)");
    }
    if(input=="DISARM"){
      //goto ALARM_DISARM;
      flagArmed=false;
      Serial.println("flagArmed.setState(FALSE)");
    }
    Serial.println("flagArmed.setState(ERROR)");
    goto ALARM_ERR;
    /*
    //Main Command Handler (DO NOT MODIFY!)
    ALARM_ARM:
    flagArmed=true;
    Serial.println("flagArmed.setState(TRUE)");
    goto ALARM_DONE;
    ALARM_DISARM:
    flagArmed=false;
    Serial.println("flagArmed.setState(FALSE)");
    goto ALARM_DONE;
    //Main Command Handler (DO NOT MODIFY!)
    */
    ALARM_DONE:
    if(flagAlarm==true){
      flagAlarm=false;
      }
    flagState = !flagState;Serial.println("flagArmed.setState(!flagSTATE)");
    }
    ALARM_ERR:
    if(flagArmed==true){
      CheckTrigger();
    }
}
/*void loop() {
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
}*/
