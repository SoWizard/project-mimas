/* 
 Controlling the 2 servos - steering and thrust

 Recall servo values are from 0 - 180
 Each packet of data is a null terminated string: XXXYYY
 XXX is from 0 - 180 for steer
 YYY is from 0 - 180 for thrust
 
 1 April 2016
 by Michel Fathallah
*/

#include <Servo.h>

#define STEERPIN   9
#define THRUSTPIN  10

// create servo objects 
Servo steer;
Servo thrust;

// ints for servo values
int steerVal;
int thrustVal; 

// Create Serial input variable
String read;

///////////////////////////////////////////////

void setup() {
  
  // Initialise Serial 
  Serial.begin(115200);
  
  // Set digital pins to out - pretty sure servo library would do this anyway
  pinMode(STEERPIN, OUTPUT);
  pinMode(THRUSTPIN, OUTPUT);
  
  // attach the servo objects to digital pin outs
  steer.attach(STEERPIN);
  thrust.attach(THRUSTPIN); 
}

///////////////////////////////////////////////

void loop()  {
  
  // Check for incoming Serial data
  // NOTE: We only want the latest command received. Not doing much error checking (partial strings etc)
  // ASSUME: That the Arduino can keep up with the serial data arriving thereby we won't get an overflow
  // TODO: Insert delay in sending?
  while (Serial.available() >= 6) {
    read = Serial.readString(); // Reads the buffer as string until null terminator is found

    // Process string (split and convert to ints)
    steerVal = (read.substring(0,3)).toInt();
    thrustVal = (read.substring(3,6)).toInt();
    
    // DEBUG: Write back serial values
    Serial.print("Steer: ");
    Serial.println(steerVal);
    Serial.print("Thrust: ");
    Serial.println(thrustVal);
    
    // Write servo - by having it inside this loop - only writing once for each command
    steer.write(steerVal);
    thrust.write(thrustVal);
    // Sometimes you'd want to turn off the signal to the servo to prevent wear
    // But it's a continuous signal
  }

} 


