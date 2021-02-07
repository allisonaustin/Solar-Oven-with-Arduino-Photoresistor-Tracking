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


void setup() {

  // Sets the four pins as Outputs
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
 
  // Hit reset on arduino, 5 seconds to turn on motor switch 
  delay(5000);
  
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

  int  Sensor1 = analogRead(sensorPin1);
  int  Sensor2 = analogRead(sensorPin2);
  int  Sensor3 = analogRead(sensorPin3);  

  /*Serial.println(analogRead(sensorPin1));
  delay(10);
  Serial.println(analogRead(sensorPin2));
  delay(10);
  Serial.println(analogRead(sensorPin3));
  delay(10);*/

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

  int  Sensor1 = analogRead(sensorPin1);
  int  Sensor2 = analogRead(sensorPin2);
  int  Sensor3 = analogRead(sensorPin3);  

  /*Serial.println(analogRead(sensorPin1));
  delay(10);
  Serial.println(analogRead(sensorPin2));
  delay(10);
  Serial.println(analogRead(sensorPin3));
  delay(10);*/

  
    SensorDif = Sensor3 - Sensor1;

    if (SensorDif < 20 ){
      goto EndFirstTrack;
    }
    }
 EndFirstTrack:   

  SensorDif = 0;
  }

void loop() {

/*  digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for (int x = 0; x < 800; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
    delay(3);
  }
  delay(1000); // One second delay

  digitalWrite(dirPin, LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for (int x = 0; x < 800; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
    delay(3);
  }
  delay(1000);
*/
  exit(0);

}
