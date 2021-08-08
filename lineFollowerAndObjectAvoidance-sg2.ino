
#include <MeUltrasonicSensor.h>
#include <MeLineFollower.h>
#include <MeMCore.h>
  

#include <SoftwareSerial.h>

MeDCMotor MotorL(M1);  
MeDCMotor MotorR(M2);
MeLineFollower lineFollower(PORT_2); //line follower
MeUltrasonicSensor ultraSensor(PORT_3);
MeInfraredReceiver infraredReceiverDecode(PORT_1);

uint8_t moveSpeed = 0;
double lineDirIndex=10;
double dist;

void setup() {
 infraredReceiverDecode.begin();
  Serial.begin(9600);
  Serial.println("InfraredReceiverDecode Start!");
}

void loop() {
  // put your main code here, to run repeatedly:

{
  uint8_t ReceiverCode;
  uint8_t buttonState;
  static uint8_t PrebuttonState = 0;

  buttonState = infraredReceiverDecode.buttonState();
  if(PrebuttonState != buttonState)
  {
    PrebuttonState = buttonState;
    Serial.print("buttonState 0x");
    Serial.println(buttonState);
  }
  if(infraredReceiverDecode.available())
  {
    ReceiverCode = infraredReceiverDecode.read();
    switch(ReceiverCode)
    {
       case IR_BUTTON_A: Serial.println("Press A."); moveSpeed = 100;
       case IR_BUTTON_B: Serial.println("Press B."); moveSpeed = 000;
       default: break;
    }
  }
}
  uint8_t moveSpeed = 100;
  dist = ultraSensor.distanceCm();
  Serial.println(dist);
  
  if(dist<9 && dist>1) 
  {
    obstacleAvoidance();      
  } else {
    lineFollow();  
  } 
}

void lineFollow(){
  int sensorStateCenter = lineFollower.readSensors();
  
  if(moveSpeed>200) {
    moveSpeed=200;
  }
  switch(sensorStateCenter)
  {
    case S1_IN_S2_IN: 
      //Serial.println("Sensor 1 and 2 are inside of black line"); 
      Forward(); // Forward    
      lineDirIndex=10;
      break;
    case S1_IN_S2_OUT: 
      //Serial.println("Sensor 2 is outside of black line"); 
      Forward(); // Forward    
      if(lineDirIndex>1) {
        lineDirIndex--;
      }       
      break;
    case S1_OUT_S2_IN: 
      //Serial.println("Sensor 1 is outside of black line"); 
      Forward(); // Forward
      if(lineDirIndex<20) {
        lineDirIndex++;
      }     
      break;
    case S1_OUT_S2_OUT: 
      //Serial.println("Sensor 1 and 2 are outside of black line"); 
      if(lineDirIndex==10){
      Backward(); // Backward
      }
      if(lineDirIndex==10.5){
      MotorL.run(-moveSpeed); // Turn right
      MotorR.run(moveSpeed/1.8);
      }
      if(lineDirIndex<10){
        TurnLeft(); // Turn left
      }
      if(lineDirIndex>10.5){
        TurnRight(); // Turn right
      }            
      break;
  }
}

void obstacleAvoidance() {
  MotorL.run(moveSpeed); // Turn left
  MotorR.run(moveSpeed);
  delay(450);
  lineDirIndex=10.5;
}

void Forward()
{
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed);
}
void Backward()
{
  MotorL.run(moveSpeed);
  MotorR.run(-moveSpeed);
}
void TurnLeft()
{
  MotorL.run(-moveSpeed/10); // Turn left
  MotorR.run(moveSpeed);
}
void TurnRight()
{
  MotorL.run(-moveSpeed); // Turn right
  MotorR.run(moveSpeed/10);
}
void Stop()
{
  MotorL.run(0);
  MotorR.run(0);
}
