// AlarmUno V1.0.4_r1
// Author: MACAULAY WOOLLEY
// Description:
// A simple alarm program with serial input. This accepts commands in the form of
// strings to be used to arm or disarm the alarm. It can also read button state 
// from the defined button pins to check if buttons are pressed and toggle state
// as necessary if a serial window or interface is not present.

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
  Serial.println("AlarmUno v1.0.4_r1");
  delay(500);
  while (!Serial);
  Serial.println("ALARM PROGRAM READY!");
  Serial.println("COMMANDS: ARM - Arms alarm, DISARM - Disarms alarm.");
}
void loop() {
  ArmedCheck(flagArmed); // Checks if alarm is armed.
  //Board pins are checked first if attached buttons are pressed.
  btn_sta_1 = digitalRead(btn_pin_1);
  if (btn_sta_1==false){
    if (flagAlarm==true){ //Checks if flagAlarm is true
      flagAlarm=false;
      //If true, sets to false so alarm won't sound after disarming & rearming.
    }
    flagState = !flagState;
    while(digitalRead(btn_pin_1)){
      //Do nothing until button goes HIGH.
    }
  delay(250); //debounce
  }
  //Serial buffer is then checked if anything is entered.
  if (Serial.available()){//Enables keyboard input. (input will accept any value)
    String input = ""; //Defines the input variable as a string. It also flushes the variable (see below).
    //Flushes the 'input' variable on each pass so that the input does not get mixed up with the old command.
    while (Serial.available() > 0){
      input += (char) Serial.read(); 
      //^ This line parses the input as a variable to be used in command execution.
      delay(5); //Delay for 5 ms so next character has time to be received.
    }
    input.trim(); //Forcefully removes /n if Serial Input contains newline.
    
    if(input=="ARM"||input=="arm"){ 
      goto ALARM_ARM;
    }
    if(input=="DISARM"||input=="disarm"){
      goto ALARM_DISARM;
    }
    else{
      //Serial.print(">>");Serial.print(input);
      Serial.println("ERROR! Please check command input.");
      goto ALARM_ERROR;  
    }
    //SERIAL Command Handler (DO NOT MODIFY!)
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
    //SERIAL Command Handler (DO NOT MODIFY!)
    
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
