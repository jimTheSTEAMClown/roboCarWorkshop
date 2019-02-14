// ============================================================================
// Source: STEAM Clown - www.steamclown.org 
// GitHub: https://github.com/jimTheSTEAMClown
// Hacker: Jim Burnham - STEAM Clown, Engineer, Maker, Propmaster & Adrenologist 
// This example code under the GNU Lesser General Public License v3.0
// and any docs and lesson examples is licensed under the CC BY-NC-SA 3.0.
// https://creativecommons.org/licenses/by-nc-sa/3.0/
// Create Date:      07/22/2018 
// Design Name:     sensor_lab_2_STEAMClown
// Description:     adaptation of blink on http://arduino.cc/
// Dependencies: 
// Revision: 
// Revision 0.03 - Updated for Robo Car Workshop - 07/22/2018
// Revision 0.02 - Updated for SVCTE Mechatronics Class - 07/22/2018
// Revision 0.01 - Created 07/22/2018
// Additional Comments: 
//
// ============================================================================

// Distance Sensor pins and variables
int incomingByte = 0;   // for incoming serial data
// defines variables
long duration;
int distance;
int distanceReturned = 0;
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// RoboCar pins and variables

// Left Motor 
const int leftDirControl1 = 2;
const int leftDirControl2 = 3;
const int leftSpeedControlPin = 4; // Needs to be a PWM pin to be able to control motor speed

// Right Motor
const int rightDirControl1 = 5;
const int rightDirControl2 = 6;
const int rightSpeedControlPin = 7; // Needs to be a PWM pin to be able to control motor speed

byte carSpeed = 0;  // change this (0-255) to control the speed of the motors
byte leftSpeed = 0;  // change this (0-255) to control the speed of the motors
byte rightSpeed = 0;  // change this (0-255) to control the speed of the motors
int differential = 1; // this is the % difference in the speed right vs left 
/* See function for parameters, but basic are STOP, FORWARD, BACKWARD, SPINLEFT
 * SPINRIGHT, HALFTRIGHT, HALFLEFT
*/ 
char carDirection[16] = "STOP"; 
// char leftDirection = 'S'; // S=STOP, F=Forward, B=Reverse
// char rightDirection = 'S';  // S=STOP, F=Forward, B=Reverse  


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication @ 9600 baud:
  Serial.begin(9600);
  // initialize Distance Sensor Pins
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  //Define L298N Dual H-Bridge Motor Controller Pins
  pinMode(leftDirControl1,OUTPUT);
  pinMode(leftDirControl2,OUTPUT);
  pinMode(leftSpeedControlPin,OUTPUT);
  pinMode(rightDirControl1,OUTPUT);
  pinMode(rightDirControl2,OUTPUT);
  pinMode(rightSpeedControlPin,OUTPUT);

  // Stop All Motors
    allDriveMotorsStop();
    delay(1000); 
    distanceReturned=checkDistance();
    delay(5000); 

}

// the loop function runs over and over again forever
void loop() {
  carSpeed = 250;
  differential = 1;

drive("FORWARD", carSpeed, differential);    
delay(2000);
drive("STOP", 0, 1);
delay(1000);
drive("BACKWARD", carSpeed, differential);    
delay(2000);
drive("STOP", 0, 1);
delay(1000);
drive("FORWARD", carSpeed, differential);    
delay(2000);
drive("STOP", 0, 1);
delay(1000);
drive("SPINLEFT", carSpeed, differential);    
delay(2000);
drive("STOP", 0, 1);
delay(1000);
drive("SPINRIGHT", carSpeed, differential);    
delay(2000);
drive("STOP", 0, 1);
delay(1000);

//  Serial.println("Checking Distance"); 
//  delay(500);
//  distanceReturned=checkDistance();
//
//  if (distanceReturned > 20) {
//    // write code that does something when your distance threshhold is NOT found
//    drive("FORWARD", carSpeed, differential);    
//    digitalWrite(LED_BUILTIN, HIGH);
//    Serial.print(distanceReturned);
//    Serial.println(" is more than 20");
//    
//  }
//  else{
//    // write code that does something when your distance threshhold is NOT found
//    // write code that does something when your distance threshhold is found
//    // drive("BRAKESTOP", carSpeed, 1);
//    drive("STOP", 0, 1);
//    alarm();
//    Serial.println("less than 20");
//  }
//  //delay(2000); // take this out later
}

// Routines that are called in this program
int checkDistance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance= duration*0.034/2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if (distance < 10) {
    return distance;
  }
  else{
    return distance;
  }
}

void alarm(){
  // send data only when you receive data:
  for (int i = 0; i < 5; i ++)
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.print("HIGH");
    delay(100);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    Serial.println("LOW");
    delay(100);                       // wait for a second
  }
}

// ============================================================================  

void allDriveMotorsStop() {
    analogWrite(leftSpeedControlPin, 0);//Sets speed variable via PWM
    analogWrite(rightSpeedControlPin, 0);//Sets speed variable via PWM  
    digitalWrite(leftDirControl1, LOW);
    digitalWrite(leftDirControl2, LOW);
    digitalWrite(rightDirControl1, LOW); 
    digitalWrite(rightDirControl2, LOW);
    Serial.println("All Motors STOPPED");  
}

/* Function to control Direction, Speed and Differential
 * Direction Options
 * STOP
 * FORWARD
 * BACKWARD
 * SPINLEFT
 * SPINRIGHT
 * HALFLEFT - left motor is 50% less than right motor
 * HALFTRIGHT - right motor is 50% less than left motor
 * SLIGHTLEFT - left motor is some% less than right motor
 * SLIGHTRIGHT - right motor is some% less than left motor

*/
int drive(char carDirection[], int carSpeed, int differential )
  {
    int localCarSpeed = 0;
    if(carDirection=="STOP")
    {
      localCarSpeed = 0; // changes carSpeed locally
      analogWrite(leftSpeedControlPin, localCarSpeed);//Sets speed variable via PWM
      analogWrite(rightSpeedControlPin, localCarSpeed);//Sets speed variable via PWM       
      digitalWrite(leftDirControl1, LOW);
      digitalWrite(leftDirControl2, LOW);
      digitalWrite(rightDirControl1, LOW); 
      digitalWrite(rightDirControl2, LOW);
      Serial.print("car is STOPPED at a speed of ");
      Serial.println(carSpeed);      
    }
    else if(carDirection=="BRAKESTOP") // Forward
    {
      analogWrite(leftSpeedControlPin, carSpeed);//Sets speed variable via PWM
      analogWrite(rightSpeedControlPin, carSpeed);//Sets speed variable via PWM 
      digitalWrite(leftDirControl1, HIGH);
      digitalWrite(leftDirControl2, LOW);
      digitalWrite(rightDirControl1, HIGH); 
      digitalWrite(rightDirControl2, LOW);
      delay(50);
      carSpeed = 0; // changes carSpeed locally
      analogWrite(leftSpeedControlPin, carSpeed);//Sets speed variable via PWM
      analogWrite(rightSpeedControlPin, carSpeed);//Sets speed variable via PWM       
      digitalWrite(leftDirControl1, LOW);
      digitalWrite(leftDirControl2, LOW);
      digitalWrite(rightDirControl1, LOW); 
      digitalWrite(rightDirControl2, LOW);
      Serial.print("car is STOPPED at a speed of ");
      Serial.println(carSpeed);      
    }
    else if(carDirection=="FORWARD") // Forward
    {
      analogWrite(leftSpeedControlPin, carSpeed);//Sets speed variable via PWM
      analogWrite(rightSpeedControlPin, carSpeed);//Sets speed variable via PWM 
      digitalWrite(leftDirControl1, LOW);
      digitalWrite(leftDirControl2, HIGH);
      digitalWrite(rightDirControl1, LOW); 
      digitalWrite(rightDirControl2, HIGH);
      Serial.print("FORWARD at a speed of ");
      Serial.print(carSpeed);
      Serial.print(" with a Differetial of ");
      Serial.println(differential);
    }
    else if(carDirection=="BACKWARD")
    {
      analogWrite(leftSpeedControlPin, carSpeed);//Sets speed variable via PWM
      analogWrite(rightSpeedControlPin, carSpeed);//Sets speed variable via PWM 
      digitalWrite(leftDirControl1, HIGH);
      digitalWrite(leftDirControl2, LOW);
      digitalWrite(rightDirControl1, HIGH); 
      digitalWrite(rightDirControl2, LOW);
      Serial.print("car is BACKWARD at a speed of ");
      Serial.print(carSpeed); 
      Serial.print(" with a Differetial of ");
      Serial.println(differential);     
    }
    else if(carDirection=="SPINLEFT") // Spin Hard Left
    {
      analogWrite(leftSpeedControlPin, carSpeed);//Sets speed variable via PWM
      analogWrite(rightSpeedControlPin, carSpeed);//Sets speed variable via PWM       
      digitalWrite(leftDirControl1, HIGH);
      digitalWrite(leftDirControl2, LOW);
      digitalWrite(rightDirControl1, LOW); 
      digitalWrite(rightDirControl2, HIGH);
      Serial.print("car is Spinning Hard Left at a speed of ");
      Serial.print(carSpeed); 
      Serial.print(" with a Differetial of ");
      Serial.println(differential);         
    }            
    else if(carDirection=="SPINRIGHT") // Spin Hard Right
    {
      analogWrite(leftSpeedControlPin, carSpeed);//Sets speed variable via PWM
      analogWrite(rightSpeedControlPin, carSpeed);//Sets speed variable via PWM       
      digitalWrite(leftDirControl1, LOW);
      digitalWrite(leftDirControl2, HIGH);
      digitalWrite(rightDirControl1, HIGH); 
      digitalWrite(rightDirControl2, LOW);
      Serial.print("car is Spinning Hard Right at a speed of ");
      Serial.print(carSpeed);  
      Serial.print(" with a Differetial of ");
      Serial.println(differential);        
    }                
    else if(carDirection=="HALFLEFT") // Slight Left
    {
      //leftSpeed = carSpeed - (carSpeed*0.50); // Sets leftspeed variable via PWM to less than current carSpeed
      leftSpeed = 50; // Sets leftspeed variable via PWM to less than current carSpeed
      rightSpeed = carSpeed; // Sets rightspeed variable via PWM to current carSpeed
      analogWrite(leftSpeedControlPin, leftSpeed);//Sets speed variable via PWM to less than current carSpeed
      analogWrite(rightSpeedControlPin, rightSpeed);//Sets carSpeed variable via PWM 
      digitalWrite(leftDirControl1, HIGH);
      digitalWrite(leftDirControl2, LOW);
      digitalWrite(rightDirControl1, LOW); 
      digitalWrite(rightDirControl2, HIGH);
      Serial.print("car is Forward + Left at a speed of ");
      Serial.print(leftSpeed);
      Serial.print(" with a Differetial of ");
      Serial.println(differential);       
    }
    else if(carDirection=="HALFRIGHT") // Slight Right
    {
      leftSpeed = carSpeed; // Sets rightspeed variable via PWM to current carSpeed
      //rightSpeed = carSpeed - (carSpeed*0.50); // Sets rightSpeed variable via PWM to less than current carSpeed
      rightSpeed = 50; // Sets rightSpeed variable via PWM to less than current carSpeed
      analogWrite(leftSpeedControlPin, leftSpeed);//Sets speed variable via PWM to less than current carSpeed
      analogWrite(rightSpeedControlPin, rightSpeed);//Sets carSpeed variable via PWM 
      digitalWrite(leftDirControl1, LOW);
      digitalWrite(leftDirControl2, HIGH);
      digitalWrite(rightDirControl1, HIGH); 
      digitalWrite(rightDirControl2, LOW);
      Serial.print("car is Forward + Right at a speed of ");
      Serial.print(rightSpeed);
      Serial.print(" with a Differetial of ");
      Serial.println(differential);       
    }
    else if(carDirection=="SLIGHTLEFT") // Slight Left
    {
      leftSpeed = carSpeed - (carSpeed*differential); // Sets leftspeed variable via PWM to less than current carSpeed
      //leftSpeed = 50; // Sets leftspeed variable via PWM to less than current carSpeed
      rightSpeed = carSpeed; // Sets rightspeed variable via PWM to current carSpeed
      analogWrite(leftSpeedControlPin, leftSpeed);//Sets speed variable via PWM to less than current carSpeed
      analogWrite(rightSpeedControlPin, rightSpeed);//Sets carSpeed variable via PWM 
      digitalWrite(leftDirControl1, HIGH);
      digitalWrite(leftDirControl2, LOW);
      digitalWrite(rightDirControl1, LOW); 
      digitalWrite(rightDirControl2, HIGH);
      Serial.print("car is Forward + Left at a speed of ");
      Serial.print(leftSpeed);
      Serial.print(" with a Differetial of ");
      Serial.println(differential);       
    }
    else if(carDirection=="SLIGHTRIGHT") // Slight Right
    {
      leftSpeed = carSpeed; // Sets rightspeed variable via PWM to current carSpeed
      rightSpeed = carSpeed - (carSpeed*differential); // Sets rightSpeed variable via PWM to less than current carSpeed
      //rightSpeed = 50; // Sets rightSpeed variable via PWM to less than current carSpeed
      analogWrite(leftSpeedControlPin, leftSpeed);//Sets speed variable via PWM to less than current carSpeed
      analogWrite(rightSpeedControlPin, rightSpeed);//Sets carSpeed variable via PWM 
      digitalWrite(leftDirControl1, LOW);
      digitalWrite(leftDirControl2, HIGH);
      digitalWrite(rightDirControl1, HIGH); 
      digitalWrite(rightDirControl2, LOW);
      Serial.print("car is Forward + Right at a speed of ");
      Serial.print(rightSpeed);
      Serial.print(" with a Differetial of ");
      Serial.println(differential);       
    }    
    else
    {
      Serial.print("ERROR ");
      Serial.print(carDirection);
      Serial.print(". ");
      Serial.println(carSpeed);
      Serial.print(". ");
      Serial.println(differential);
      analogWrite(leftSpeedControlPin, carSpeed);//Sets speed variable via PWM
      analogWrite(rightSpeedControlPin, carSpeed);//Sets speed variable via PWM       
      digitalWrite(leftDirControl1, LOW);
      digitalWrite(leftDirControl2, LOW);
      digitalWrite(rightDirControl1, LOW); 
      digitalWrite(rightDirControl2, LOW);
      Serial.print("car is Stopped but there was a direction command error");   
    }

}
