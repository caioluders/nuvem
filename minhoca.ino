#include "Ultrasonic.h"

#define echoPin 11
#define trigPin 13

// right = MotorDois
// left = MotorPin

int MotorPin =  A0 ;
int MotorDois =  A1 ;
int inPin = 12 ;
boolean valor ;
boolean anterior = false ;
int parou = 0 ;
int lado = 0 ;
unsigned long cont = 0 ;  


Ultrasonic ultrasonic(13,11);

boolean bw() {
  valor = digitalRead(inPin);
  if ( valor == HIGH ) {
    return true ;
  } 
  if ( valor == LOW ) {
    return false ;
  } 
}

void WALK_MORE() {
  if ( (cont % 2) == 0 ) {
    analogWrite(MotorDois, 130);
    analogWrite(MotorPin, 0);
  } else if ( (cont % 2) == 1 ) {
    analogWrite(MotorDois, 0);
    analogWrite(MotorPin, 130);
  }
}

void WALK( boolean respect ) {
  if ( respect == true && respect != anterior ) {
    anterior = respect ;
    cont++ ;
    WALK_MORE() ;
  } 
  else if ( respect == false && anterior != respect  ) {
    anterior = respect ;
  }
}

void viravira ( int distancia ) {
  if ( ( distancia >= 1 ) && ( distancia <= 20 ) ){
    analogWrite(MotorDois, 0);
    analogWrite(MotorPin, 255);
    delay(450) ;
    analogWrite(MotorDois, 255);
    analogWrite(MotorPin, 255);
    delay(500) ;
    analogWrite(MotorDois, 255);
    analogWrite(MotorPin, 0);
    delay(450) ;
    analogWrite(MotorDois, 255);
    analogWrite(MotorPin, 255);
    delay(500) ;
    analogWrite(MotorDois, 255);
    analogWrite(MotorPin, 0);
    delay(450) ;
    analogWrite(MotorDois, 255);
    analogWrite(MotorPin, 255);
    delay(450) ;
    analogWrite(MotorDois, 0);
    analogWrite(MotorPin, 0);
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(inPin , INPUT);
  pinMode(echoPin , INPUT) ;
  pinMode(trigPin , OUTPUT) ;
  pinMode(MotorPin, OUTPUT);
  pinMode(MotorDois, OUTPUT);
}

void loop() {
  valor = bw() ;
  WALK(valor) ;

  digitalWrite(trigPin, LOW ) ;
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH) ;
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW ) ;
  int distancia = (ultrasonic.Ranging(CM)) ;
  viravira( distancia ) ;

  valor = bw() ;
  WALK(valor) ;

}
