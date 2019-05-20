// AlarmUno V1.0.2_b5
// Author: MACAULAY WOOLLEY
// Description:
// A simple alarm program with serial input. This accepts commands in the form of 
// strings to be used to arm or disarm the alarm. It was adapted from the initial 
// version of the code which used buttons as inputs to work with serial inputs 
// from an external computer.

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
      input += (String) Serial.read(); //This line parses the input as a variable to be used in command execution.
      delay(5); //Delay for 5 ms so next character has time to be received.
      content.concat(character);
    }
    Serial.print(">>");Serial.println(input);
    if (input=="65827710"){
      //goto ALARM_ARM;
      flagArmed=true;
      Serial.print(">>");Serial.println(input);
      Serial.println("flagArmed.setState(TRUE)");
      goto ALARM_DONE;
    }
    if(input=="68738365827710"){
      //goto ALARM_DISARM;
      flagArmed=false;
      Serial.print(">>");Serial.println(input);
      Serial.println("flagArmed.setState(FALSE)");
      goto ALARM_DONE;
    }
    Serial.println("flagArmed.setState(ERROR)");
    goto ALARM_ERROR;
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
    ALARM_ERROR:
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
