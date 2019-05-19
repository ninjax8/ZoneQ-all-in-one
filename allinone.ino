#include <TFMini.h>
#include <elapsedMillis.h>
#include <Q2HX711.h>

TFMini tfmini;

elapsedMillis rel1;
elapsedMillis rel2;
elapsedMillis rel3;
elapsedMillis rel4;

boolean rel1State = LOW;
boolean rel2State = LOW;
boolean rel3State = LOW;
boolean rel4State = LOW;

int interval1 = 400;
int interval2 = 300;
int interval3 = 500;
int interval4 = 200;

const int relayPin1 = 2;
const int relayPin2 = 4;
const int relayPin3 = 6;
const int relayPin4 = 8;

const byte DataPin1 = A15;
const byte CLKPin1 = A14;

const byte DataPin2 = A13;
const byte CLKPin2 = A12;

Q2HX711 cell1(DataPin1, CLKPin1);
Q2HX711 cell2(DataPin2, CLKPin2);

int cell1_Read;
int cell2_Read;

int interval = 1000;
unsigned long time_now = 0;

const int piezo1 = A2;
const int piezo2 = A1;
const int piezo3 = A0;
const int sonarPin = A3;
// thresholds for piezos 
const int threshold1 = 0;
const int threshold2 = 0;
const int threshold3 = 0;

int piezo1Read = 0;
int piezo2Read = 0;
int piezo3Read = 0;
int sonarVal;
int dist_cm = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(15200);
  tfmini.begin(&Serial1);
  pinMode(piezo1,INPUT);
  pinMode(piezo2,INPUT);
  pinMode(piezo3,INPUT);
  pinMode(sonarPin,INPUT);
  pinMode(relayPin1,OUTPUT);
  pinMode(relayPin2,OUTPUT);
  pinMode(relayPin3,OUTPUT);
  pinMode(relayPin4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t dist = tfmini.getDistance();
  piezo1Read = analogRead(piezo1);
  piezo2Read = analogRead(piezo2);
  piezo3Read = analogRead(piezo3);
  sonarVal = analogRead(sonarPin);
  dist_cm = (sonarVal*1.262);
  cell1_Read = (cell1.read()/10000.0);
  cell2_Read = (cell2.read()/10000.0);
  
  if(millis() > time_now + interval){
    time_now = millis();  
  
  Serial.print("Piezo 1: ");
  Serial.println(piezo1Read);
  Serial.print("Piezo 2: ");
  Serial.println(piezo2Read);
  Serial.print("Piezo 3: ");
  Serial.println(piezo3Read);
  Serial.print("Distance: ");
  Serial.println(dist_cm);
  Serial.print("Loadcell 1: ");
  Serial.println(cell1_Read);
  Serial.print("Loadcell 2: ");
  Serial.println(cell2_Read);
  Serial.print("From LiDAR");
  Serial.println(dist);
  }
  if (rel1 > interval1) 
  {        
      rel1State = !rel1State;         // toggle the state from HIGH to LOW to HIGH to LOW ... 
      digitalWrite(relayPin1, rel1State);
      rel1 = 0;              // reset the counter to 0 so the counting starts over...
  }

  if (rel2 > interval2) 
  {        
      rel2State = !rel2State;         // toggle the state from HIGH to LOW to HIGH to LOW ... 
      digitalWrite(relayPin2, rel2State);
      rel2 = 0;              // reset the counter to 0 so the counting starts over...
  }

  if (rel3 > interval3) 
  {        
      rel3State = !rel3State;         // toggle the state from HIGH to LOW to HIGH to LOW ... 
      digitalWrite(relayPin3, rel3State);
      rel3 = 0;              // reset the counter to 0 so the counting starts over...
  }

  if (rel4 > interval4) 
  {        
      rel4State = !rel4State;         // toggle the state from HIGH to LOW to HIGH to LOW ... 
      digitalWrite(relayPin4, rel4State);
      rel4 = 0;              // reset the counter to 0 so the counting starts over...
  }
}
