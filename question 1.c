include <stdio.h>

//declare variable
float current_ feedback;
float current_reference;
float voltage_feedback;
float voltage_reference;
  float minimum_current;
  bool enable_command ;
  float current_error;
  float voltage_error;
  float current_integral;
  float voltage_integral;
  float current_output;
  float voltage_output;
  int state;

const float Iref = 1.0; // current reference
const float Vref= 4.2; // current reference 
const float Imin = 0.3 ; // min current 
const float Kp_current = 0.2;// can change according desire 
const float Ki_current = 0.02;// can change according desire
const float Kp_voltage = 0.3;// can change according desire
const float Ki_volatge = 0.03;// can change according desire

   
void Initialization(void){
current_ feedback=0.0;
voltage_feedback = 0.0;
current_error = 0.0;
voltage_error= 0.0;
current_integral = 0.0;
voltage_integral = 0.0;
current_output = 0.0;
voltage_output = 0.0;
enable_command = false;
state = 0; // set initial state to idle mode
}



void control_routine(void){
//current control
current_error = Iref – current_feedback;
current_intergral += current_error;
current_output = Kp_current * current_error + Ki_current * current_integral 
// Voltage control
voltage_error = Vref –voltage_feedback;
voltage_intergral += voltage_error;
voltage_output = Kp_voltage * voltage_error + Ki_voltage * voltage_integral 

}

void main_state_machine(void){

switch (state){
case 0 :// idle state
 if ( enable_command == true){
state = 1;
}
else ( enable_command ==false ){
state = 0;
}
break;

case 1 : // constant current state

control_routine();// run control algorithm to check conditon
if (voltage_feedback>=Vref){
state = 2;// go to constant voltage state
}

break;

case 2 : // constant voltage state
control_routine();
if (current_feedback>=Imin){
enable_command = false;//stop charging
state = 0;// go to idle state 

}
break;
}

void main(void){
Initialization();
PieVectTable.EPWM1_INT = &control_routine;
while(true){
main_state_machine();
}

