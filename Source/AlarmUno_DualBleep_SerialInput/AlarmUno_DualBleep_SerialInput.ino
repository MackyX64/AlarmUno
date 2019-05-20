// AlarmUno V1.0.1
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
  PinSetup_init(); Serial.print("Initializing Board Pins... ");
  delay(100);Serial.println("Done");
  MFShield_init();Serial.print("Initializing MFShield... ");
  delay(100);Serial.println("Done");
  Serial.println("Initialisation Complete! Starting Program...");
  delay(500);
  while (!Serial);
  Serial.println("===================================================");
  Serial.println("AlarmUno v1.0.1");
  Serial.println("Commands: ARM - Arms alarm, DISARM - Disarms alarm.");
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
    Serial.print(">>");Serial.println(input); //Displays inputted command. Can be commented out if not needed.
    if (input=="ARM" or "arm"){
      flagArmed=true;
      Serial.println("ALARM ARMED"); // Tells the user that Alarm is ARMED.
      goto ALARM_DONE; //Tells the program to skip ahead to ALARM_DONE line of program.
    }
    if(input=="DISARM" or "disarm"){
      flagArmed=false;
      Serial.println("ALARM DISARMED"); // Tells the user that Alarm is DISARMED.
      goto ALARM_DONE; //Tells the program to skip ahead to ALARM_DONE line of program.
    }
    else{
      Serial.println("ERROR! Invalid Command!");
      //Error Handler which tells the user the input is incorrect.
    }
  }
  ALARM_DONE:
  if(flagArmed==true){
    CheckTrigger();
  }
}
