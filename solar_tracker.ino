#include <AccelStepper.h>


int sensorValue2;
int sensorValue1;
AccelStepper Motor1(1, 5, 4);            // pin 3 = step, pin 6 = direction

void setup() {
  Serial.begin(9600);
  Motor1.setMaxSpeed(400);
}





void stepperCheck(){
if(sensorValue1-150>sensorValue2){
  Motor1.setSpeed(400);
}
else if(sensorValue2-150>sensorValue1){
  Motor1.setSpeed(-400);
}
else{
 Motor1.setSpeed(0);
}
}




void loop() {
  // read the input on analog pin 0:
  stepperCheck();
  Motor1.runSpeed();
  sensorValue1 = analogRead(A0);
  sensorValue2 = analogRead(A1);

  // print out the value you read:
 /* Serial.print("Sensor1:");
  Serial.print(sensorValue1);
  Serial.print("--Sensor2:");
  Serial.println(sensorValue2);
*/
}
