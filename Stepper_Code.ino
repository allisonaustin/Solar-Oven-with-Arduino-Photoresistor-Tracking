
int sensorPin1 = A1;
int sensorPin2 = A3;
int sensorPin3 = A5;

const int stepPin1 = 6;
const int dirPin1 = 8;
const int stepPin2 = 2;
const int dirPin2 = 4;

//int azValue = 0; //azimuth value
//int altValue = -4000; //always begins facing south with mirror arm fully down (0,-400) x equals right and left, y equals up and down

int SensorDif ;

  void setup() {
  
  pinMode(stepPin1,OUTPUT);
  pinMode(dirPin1,OUTPUT);

  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin2,OUTPUT);

delay(5000); //five second delay

Serial.begin(9600);

  digitalWrite(dirPin1,LOW);
  for(int x = 0; x < 4000; x++) {
    digitalWrite(stepPin1,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1,LOW);
    delayMicroseconds(500);
    delay(3);
  }
  
   digitalWrite(dirPin1,HIGH);
   for(int x = 0; x < 8000; x++) {
    digitalWrite(stepPin1,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1,LOW);
    delayMicroseconds(500);
    delay(3);
//    azValue = azValue + 1;

 int sensorValue1 = analogRead(sensorPin1);
 int sensorValue2 = analogRead(sensorPin2);
 int sensorValue3 = analogRead(sensorPin3);

 SensorDif = sensorValue2 - sensorValue1;
   
   if(SensorDif < 20) {
    goto ElevationSearch; 
    }
   }

ElevationSearch:
/*Now move the elevation tracker until light strikes the bottom sensor(since light is already on sensor 1*/

    digitalWrite(dirPin2,HIGH);
      for(int x = 0; x < 8000; x++); {
      digitalWrite(stepPin2,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2,LOW);
      delayMicroseconds(500);
      delay(3);
   // altValue = altValue + 1;
 
 int sensorValue1 = analogRead(sensorPin1);
 int sensorValue2 = analogRead(sensorPin2);
 int sensorValue3 = analogRead(sensorPin3);

    SensorDif = sensorValue3 - sensorValue1;

    if(SensorDif < 20) {
      goto EndFirstTrack;
    }
   }
  
EndFirstTrack:
    
    SensorDif = 0;
}

void loop() {

exit(0);

}
