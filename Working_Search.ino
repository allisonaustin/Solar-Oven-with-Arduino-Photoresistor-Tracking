// defines pin numbers for the step motor control
const int stepPin1 =6;
const int dirPin1 = 8;
const int stepPin2 = 2;
const int dirPin2 = 4;

int SensorDif ;

// select the analog input pins for the photoresistors
int sensorPin1 = A1; 
int sensorPin2 = A3;
int sensorPin3 = A5;

int sensorValue1;
int sensorValue2;
int sensorValue3;
int sensorValue11;
int sensorValue22;
int sensorValue33;

int azimuth; //with the oven positioned in the center facing south, it can move 4000 "pulses" east or west
// south is defined as azimuth 4000, with azimuth limits of 0 (east) to 8000 (west)

int elevation; //with the oven facing the horizon, it can move 8000 "pulses" to where it points directly overhead

void setup() {

  // Sets the four pins as Outputs
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
 
  // Hit reset on arduino, 3 seconds to turn on motor switch 
  delay(3000);
  
  Serial.begin(9600);

/*Moves Azimuth tracker to its most easterly postion*/

  digitalWrite(dirPin1, LOW); 
  for (int x = 0; x < 4000; x++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
    delay(3);
  }
/*Now move the azimuth tracker to the west until the light strikes sensor 2 (eastern sensor) */

  digitalWrite(dirPin1, HIGH); 
  for (int x = 0; x < 8000; x++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
    delay(3);

  int  sensorValue1 = analogRead(sensorPin1);
  int  sensorValue2 = analogRead(sensorPin2);
  int  sensorValue3 = analogRead(sensorPin3);  


    SensorDif = sensorValue2 - sensorValue1;

    if (SensorDif < 10 ){
      goto ElevationSearch;
    }
    }
ElevationSearch:

/*Now move the elevation tracker until light strikes the bottom sensor (since light is already on sensor 1*/

  digitalWrite(dirPin2, HIGH); 
  for (int x = 0; x < 8000; x++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
    delay(3);

  int  sensorValue1 = analogRead(sensorPin1);
  int  sensorValue2 = analogRead(sensorPin2);
  int  sensorValue3 = analogRead(sensorPin3);  

  
    SensorDif = sensorValue3 - sensorValue1;

    if (SensorDif < 10 ){
      goto EndFirstTrack;
    }
    }
 EndFirstTrack:   

  SensorDif = 0;
  }

void loop() {

StartLoop:

  delay(3000); //three second delay

  //Checking for sensor shading

    sensorValue11 = analogRead(sensorPin1);
    sensorValue22 = analogRead(sensorPin2);
    sensorValue33 = analogRead(sensorPin3);

 //check for cloud shading, all sensor values will have risen

//Because the sun is moving to the west, sensorValue1 can only be shaded due to sun elevation drop

     SensorDif = sensorValue11 - sensorValue1;


  if (SensorDif > 100) {

  digitalWrite(dirPin2, LOW);
   for (int x = 0; x < 100; x++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
    delay(3); 
   }
    sensorValue11 = analogRead(sensorPin1);
    SensorDif = sensorValue11 - sensorValue1;
  }

//Because the sun is moving to the west, and shading caused by an elevation drop is already corrected,
//Sensor2 shading can only be caused by an azimuth change to the west
   
   SensorDif = sensorValue22 - sensorValue2;

  if (SensorDif > 100) {

  digitalWrite(dirPin1, HIGH);
   for (int x = 0; x < 100; x++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
    delay(3); 
   }
    sensorValue22 = analogRead(sensorPin2);
    SensorDif = sensorValue22 - sensorValue2;
   }

//Because the sun is moving west, Sensor3 can only be shaded due to a sun elevation rise
  
       SensorDif = sensorValue33 - sensorValue3;

  if (SensorDif > 100) {
    digitalWrite(dirPin2, HIGH);
     for (int x = 0; x < 100; x++) {
       digitalWrite(stepPin2, HIGH);
       delayMicroseconds(500);
       digitalWrite(stepPin2, LOW);
       delayMicroseconds(500);
       delay(3); 
   }
      sensorValue33 = analogRead(sensorPin3);
      SensorDif = sensorValue33 - sensorValue3;
   }  

}
