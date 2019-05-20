// Global Variables (Constant)
const int btn_pin_1 = A1; //Defines button A1 to variable.
const int btn_pin_2 = A2; //Defines button A2 to variable.
const int btn_pin_3 = A3; //Defines button A3 to variable.
const int spk_pin_1 = 5;  //Defines pin for external speaker component.
// Global Variables (Changing)
int btn_sta_1 = A1; //Defines button switch state variable for A1.
int btn_sta_2 = A2; //Defines button switch state variable for A2.
int btn_sta_3 = A3; //Defines button switch state variable for A3.
bool flagState = false; //Defines flagState to toggle button logic.
bool flagArmed = false; //Defines flagState to check if alarm is armed.
bool flagAlarm = false; //Defines flagState if alarm is triggered.

//Run Init Setups (Configuring pin modes on board)
void PinSetup_init(){
  // Defines the input button pins to input mode.
  pinMode(btn_pin_1, INPUT); //Defines pin mode of sw_pin_1 (A1)
  pinMode(btn_pin_2, INPUT); //Defines pin mode of sw_pin_2 (A2)
  pinMode(btn_pin_3, INPUT); //Defines pin mode of sw_pin_3 (A3)
}
//Run Init Setups (Initializes MFShield with Timer1 Library)
void MFShield_init(){
  // MFShield initialize subroutine.
  Timer1.initialize();
  MFS.initialize(&Timer1);
  MFS.write("8888");
  delay(250);
  MFS.write("----");
  delay(250);
  MFS.write("BOOT");
  delay(500);
}
