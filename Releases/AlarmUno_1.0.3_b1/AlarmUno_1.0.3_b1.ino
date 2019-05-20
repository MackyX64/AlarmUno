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
  Serial.println("AlarmUno v1.0.2_r1");
  delay(500);
  while (!Serial);
  Serial.println("ALARM PROGRAM READY!");
  Serial.println("COMMANDS: ARM - Arms alarm, DISARM - Disarms alarm.");
}
void loop() {
  ArmedCheck(flagArmed); // Checks if alarm is armed.
  if (Serial.available()){//Enables keyboard input. (input will accept any value)
    String input = ""; //Defines the input variable as a string. It also flushes the variable (see below).
    //Flushes the 'input' variable on each pass so that the input does not get mixed up with the old command.
    while (Serial.available() > 0){
      input += (char) Serial.read(); 
      //^ This line parses the input as a variable to be used in command execution.
      delay(5); //Delay for 5 ms so next character has time to be received.
    }
    input.trim(); //Forcefully removes /n if Serial Input contains newline.
    if(input=="arm"){ 
      goto ALARM_ARM;
    }
    if(input=="disarm"){
      //goto ALARM_DISARM;
    }
    else{
      //Serial.print(">>");Serial.print(input);
      Serial.println("ERROR! Please check command input.");
      goto ALARM_ERROR;  
    }
    
    //Main Command Handler (DO NOT MODIFY!)
    ALARM_ARM:
    flagArmed=true;
    Serial.print(">>");Serial.println(input);
    Serial.println("Alarm is Armed!");
    goto ALARM_DONE;
    ALARM_DISARM:
    flagArmed=false;
    Serial.print(">>");Serial.println(input);
    Serial.println("Alarm is Disarmed.");
    goto ALARM_DONE;
    //Main Command Handler (DO NOT MODIFY!)
    
    ALARM_DONE:
    if(flagAlarm==true){
      flagAlarm=false;
      }
    flagState = !flagState;
    }
    ALARM_ERROR:
    if(flagArmed==true){
      CheckTrigger();
    }
}
