#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define ENA A2      // Motor A Enable 
#define motor1A 9     // INA 
#define motor1B 10     // INB
#define motor2A 5     // INC
#define motor2B 6     // IND
#define ENB A3		  // Motor B Enable
int say = 2;
void setup(){
  Serial.begin(9600);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  pinMode(motor1A, OUTPUT); //solteker
  pinMode(motor1B, OUTPUT); //solteker
  pinMode(motor2A, OUTPUT); //sagteker
  pinMode(motor2B, OUTPUT); //sag teker
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(11, OUTPUT);
  
  // L298n aktivlesdir 
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  delay(2000);
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));
  lox.startRangeContinuous();
}

void loop(){
  int mesafe = lox.readRange();
  Serial.print("Distance in mm: ");
  Serial.println(mesafe);

  analogWrite(11, 127);

  qabaga();

  if(mesafe < 100){
    dayan();
    say++;
    delay(2000);
    if(say==6){
      while(1){
        dayan();
      }
    }
    if(say%2==0){ //qalig sifirdisa cutdu
      sola180();
    }else{ //
      saga180();
    }
  }
  
  
}

void sola180(){
  soladon();
  delay(1250);
  dayan();
  delay(2000);
}

void saga180(){
  sagadon();
  delay(1100);
  dayan();
  delay(2000);
}

void qabaga(){
  analogWrite(motor1A, 70);
  digitalWrite(motor1B, 0);
  digitalWrite(motor2A, 0); //sag teker
  analogWrite(motor2B, 85); //sag teker
}

void soladon(){
  digitalWrite(motor1A, 0);
  analogWrite(motor1B, 0);
  digitalWrite(motor2A, 0);
  analogWrite(motor2B, 85);
}

void sagadon(){
  analogWrite(motor1A, 70); //sol teker qabaga
  digitalWrite(motor1B, 0);
  analogWrite(motor2A, 0);
  digitalWrite(motor2B, 0);
}

void dayan(){
  digitalWrite(motor1A, 0);
  digitalWrite(motor1B, 0);
  digitalWrite(motor2A, 0);
  digitalWrite(motor2B, 0);
}
