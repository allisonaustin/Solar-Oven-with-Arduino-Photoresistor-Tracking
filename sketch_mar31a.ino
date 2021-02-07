//defines pinnumbers
const int stepPin1 = 6;
const int stepPin2 = 2;
const int dirPin1 = 8;
const int dirPin2 = 4;


void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin1,OUTPUT);
  pinMode(dirPin1,OUTPUT);

  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin2,OUTPUT);



delay(5000); // Five second delay

}

void loop () { 


  digitalWrite(dirPin2,HIGH);
  for(int x = 0; x < 4000; x++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2,LOW);
    delayMicroseconds(500);
    delay(5);
  }
  exit(0);
} 
