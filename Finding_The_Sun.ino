int sensorPin1 = A1;
int sensorPin2 = A3;
int sensorPin3 = A5;

int sensorValue1; //upper west photo resistor value
int sensorValue2; //upper east photo resistor value
int sensorValue3; //lower west photo resistor value
int sensorValue11; //used for comparing later reading to earlier reading
int sensorValue22;
int sensorValue33;

int azimuth; //with the oven positioned in the center facing south, it can move 4000 "pulses" east or west
// south is defined as azimuth 4000, with azimuth limits of 0 (east) to 8000 (west)

int elevation; //with the oven facing the horizon, it can move 8000 "pulses" to where it points directly overhead

const int stepPin1 = 6;
const int dirPin1 = 8;
const int stepPin2 = 2;
const int dirPin2 = 4;

//int azValue = 0; //azimuth value
//int elValue = -4000; //always begins facing south with mirror arm fully down (0,-400) x equals right and left, y equals up and down

int SensorDif ;
int SensorDif1 ;
int SensorDif2 ;
int SensorDif3 ;

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

 SensorDif = sensorValue2-sensorValue1;
   
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
   // elValue = elValue + 1;

 int sensorValue1 = analogRead(sensorPin1);
 int sensorValue2 = analogRead(sensorPin2);
 int sensorValue3 = analogRead(sensorPin3);

    SensorDif = sensorValue3-sensorValue1;

    if(SensorDif < 20) {
      goto EndFirstTrack;
    }
   }
  EndFirstTrack:
    
    SensorDif = 0;
}

void loop() {

StartLoop:

  delay(30000);

  //Checking for sensor shading

  sensorValue11 = analogRead(sensorPin1);
  sensorValue22 = analogRead(sensorPin2);
  sensorValue33 = analogRead(sensorPin3);

 //check for cloud shading, all sensor values will have risen

 SensorDif1 = sensorValue11 - sensorValue1;
 SensorDif2 = sensorValue22 - sensorValue2;
 SensorDif3 = sensorValue33 - sensorValue3;
  
  if((SensorDif1 > 20) and (SensorDif2 > 20) and (SensorDif3 > 20)) {
    goto StartLoop; 
    }

//Because the sun is moving to the west, sensorValue1 can only be shaded due to sun elevation drop

      
    SensorDif = sensorValue11 - sensorValue1 ;

   if(SensorDif > 20) {
      digitalWrite(dirPin2,LOW);
      for(int x = 0; x < 8000; x++); {
      digitalWrite(stepPin2,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2,LOW);
      delayMicroseconds(500);
      delay(3);

 sensorValue1 = analogRead(sensorPin1);
 sensorValue3 = analogRead(sensorPin3);

    SensorDif = sensorValue1 - sensorValue3; 

   if(SensorDif < 20) {
     goto StartLoop; 
      }
    }
  }

//sensorValue2 shading can only be caused by an azimuth change to the west

    SensorDif = sensorValue22 - sensorValue2;

   if(SensorDif > 20) {
      digitalWrite(dirPin1,HIGH);
      for(int x = 0; x < 8000; x++); {
      digitalWrite(stepPin1,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1,LOW);
      delayMicroseconds(500);
      delay(3);

 sensorValue1 = analogRead(sensorPin1);
 sensorValue2 = analogRead(sensorPin2);

      SensorDif = sensorValue2 - sensorValue1;

    if(SensorDif < 20) {
      goto StartLoop;
      }
    }
  }

//Because the sun is moving west, sensorValue3 can only be shaded due to a sun elevation rise

    SensorDif = sensorValue33 - sensorValue3;
      
      if(SensorDif > 20) {
      digitalWrite(dirPin2,HIGH);
      for(int x = 0; x < 8000; x++); {
      digitalWrite(stepPin2,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2,LOW);
      delayMicroseconds(500);
      delay(3);  

     sensorValue1 = analogRead(sensorPin1);
     sensorValue3 = analogRead(sensorPin3);

        SensorDif = sensorValue3 - sensorValue1;

    if(SensorDif < 20) {
      goto StartLoop;
      }
    }
  }
}  
