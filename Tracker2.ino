// defines pin numbers for the step motor control
const int stepPin1 =6;
const int dirPin1 = 8;
const int stepPin2 = 2;
const int dirPin2 = 4;

// select the analog input pins for the photoresistors
int sensorPin1 = A1; 
int sensorPin2 = A3;
int sensorPin3 = A5;

// Declaring other variables used in the program

int Azimuth;// With the oven positioned in the center facing south, it can move 4000 "pulses" east or west.
// south is defined at azimuth 4000, with azimuth limits of 0 (east) to 8000 (west).

int Elevation;//with the oven facing the horizon, it can move 8000 "pulses" to where it points directly overhead

int SensorDif;//used to calculate differences between, or changes to, sensor values
int SensorDif1;
int SensorDif2;
int SensorDif3;

int  Sensor1; //upper-west photo resistor value
int  Sensor2; //upper-east photo resistor value
int  Sensor3; //lower-west photo resistor value
int  Sensor11; //used for comparing later reading to ealier reading of sensor1
int  Sensor22;
int  Sensor33; 

void setup() {

  // Sets the four pins as Outputs
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
 
  // position the oven and mirrors, Hit reset on arduino, 5 seconds to turn on motor switch 
  delay(5000);
  Elevation = 0;
  Azimuth = 0;
  
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
    Azimuth = Azimuth + 1;
    
    Sensor1 = analogRead(sensorPin1);
    Sensor2 = analogRead(sensorPin2);
    Sensor3 = analogRead(sensorPin3);  

   SensorDif = Sensor2 - Sensor1;

    if (SensorDif < 20 ){
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
    Elevation = Elevation + 1;
    Sensor1 = analogRead(sensorPin1);
    Sensor2 = analogRead(sensorPin2);
    Sensor3 = analogRead(sensorPin3);  

    SensorDif = Sensor3 - Sensor1;

    if (SensorDif < 20 ){
      goto EndFirstTrack;
    }
    }
 EndFirstTrack:   

  SensorDif = 0;
  }

void loop() {

StartLoop:
  
  delay(3000);

//Get updated values for the sensors

    Sensor11 = analogRead(sensorPin1);
    Sensor22 = analogRead(sensorPin2);
    Sensor33 = analogRead(sensorPin3);  

//Because the sun is moving to the west, Sensor1 can only be shaded due to sun elevation drop

    SensorDif = Sensor11 - Sensor1;


  if (SensorDif > 100) {

  digitalWrite(dirPin2, LOW);
   for (int x = 0; x < 100; x++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
    delay(3); 
   }
    Sensor11 = analogRead(sensorPin1);
    SensorDif = Sensor11 - Sensor1;
  }

//Because the sun is moving to the west, and shading caused by an elevation drop is already corrected,
//Sensor2 shading can only be caused by an azimuth change to the west
   
   SensorDif = Sensor22 - Sensor2;

  if (SensorDif > 100) {

  digitalWrite(dirPin1, HIGH);
   for (int x = 0; x < 100; x++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
    delay(3); 
   }
    Sensor22 = analogRead(sensorPin2);
    SensorDif = Sensor22 - Sensor2;
   }

//Because the sun is moving west, Sensor3 can only be shaded due to a sun elevation rise
  
       SensorDif = Sensor33 - Sensor3;

  if (SensorDif > 100) {
    digitalWrite(dirPin2, HIGH);
     for (int x = 0; x < 100; x++) {
       digitalWrite(stepPin2, HIGH);
       delayMicroseconds(500);
       digitalWrite(stepPin2, LOW);
       delayMicroseconds(500);
       delay(3); 
   }
      Sensor33 = analogRead(sensorPin3);
      SensorDif = Sensor33 - Sensor3;
   }

//  exit(0);

}
