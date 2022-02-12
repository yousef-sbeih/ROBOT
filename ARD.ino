#include <util/atomic.h> // For the ATOMIC_BLOCK macro

#define ENCA 2
#define ENCB 3 
int posi = 0 ;

//RIGHT WHEEL
int Motor1Input1 = 9;
int Motor1Input2 = 8;
//LEFT WHEEL
int Motor2Input1 = 7;
int Motor2Input2 = 6;

int ENCMotor1A = 10;
int ENCMotor1B = 11;

int ENCMotor2A = 12;
int ENCMotor2B = 13;

//FORWARD SENSOR
int EchoPin1 = A0;
int TrigPin1 = A1;
//RIGHT SENSOR
int EchoPin2 = A2;
int TrigPin2 = A3;
//LEFT SENSOR
int EchoPin3 = A4;
int TrigPin3 = A5;

//FORWARD
int Sonic1Reading;
//RIGHT
int Sonic2Reading;
//LEFT
int Sonic3Reading;


void setup() {
  pinMode(EchoPin1, INPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(EchoPin3,INPUT);
  
  pinMode(TrigPin1, OUTPUT);
  pinMode(TrigPin2, OUTPUT);
  pinMode(TrigPin3, OUTPUT);

  pinMode(ENCMotor1A, INPUT);
  pinMode(ENCMotor1B, INPUT);

  pinMode(ENCMotor2A, INPUT);
  pinMode(ENCMotor2B, INPUT);
  Serial.begin(9600);
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);


}

void UltraSonicReading(){
  long duration1;
  long duration2;
  long duration3;
  
  digitalWrite(TrigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin1, LOW);
  duration1 = pulseIn(EchoPin1, HIGH);
  Sonic1Reading = duration1 * 0.034 / 2;

  digitalWrite(TrigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin2, LOW);
  duration2 = pulseIn(EchoPin2, HIGH);
  Sonic2Reading = duration2 * 0.034 / 2;

  digitalWrite(TrigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin3, LOW);
  duration3 = pulseIn(EchoPin3, HIGH);
  Sonic3Reading = duration3 * 0.034 / 2;
  

}

void MoveForward(){
  
  digitalWrite(Motor1Input1, HIGH);
  digitalWrite(Motor1Input2, LOW);

  
  digitalWrite(Motor2Input1, LOW);
  digitalWrite(Motor2Input2, HIGH);
}

void MoveRight(){
  
  digitalWrite(Motor2Input1, LOW);
  digitalWrite(Motor2Input2, LOW);
   while(posi <8){
      Serial.println(posi);
    digitalWrite(Motor1Input1, HIGH);
    digitalWrite(Motor1Input2, LOW);
  }
 
    digitalWrite(Motor1Input1, LOW);
    digitalWrite(Motor1Input2, LOW);
    delay(1000);
}

void MoveLeft(){
  digitalWrite(Motor1Input1, LOW);
  digitalWrite(Motor1Input2, LOW);
 // delay(500);

  
    digitalWrite(Motor2Input1, LOW);
    digitalWrite(Motor2Input2, HIGH);
    //delay(500);
}

void loop() {
  UltraSonicReading();
  //delay(500);
  //Serial.println(Sonic1Reading);
  if(Sonic2Reading > 7){

    MoveRight();
   // delay(1000);
  }
  else{
    if(Sonic3Reading > 7){
      MoveLeft();
      //delay(2000);
    }
    else if(Sonic1Reading > 7){
      MoveForward();
      //delay(2000);
    }
    else if(Sonic1Reading < 7){
      digitalWrite(Motor1Input1, LOW);
      digitalWrite(Motor1Input2, LOW);
      digitalWrite(Motor2Input1, LOW);
      digitalWrite(Motor2Input2, LOW);
    }
    
    
  }
 

}
void readEncoder(){
  int b = digitalRead(ENCB);
  
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}
