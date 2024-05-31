#include <SPI.h>
#include <LoRa.h>
#define SS 15
#define RST 16
#define DIO0 4
float latitude,longitude;
String lat_str ="13.987699";
String lng_str ="80.237894";
String loc = lat_str +":"+ lng_str;


const int pulse = A0;
const int temp = D3;
const int relay = D4;
const int xPin = D1;
float pulsev,tempv;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
  pinMode(pulse,INPUT);
  pinMode(temp,INPUT);
  pinMode(relay,OUTPUT);
  while (!Serial);
   LoRa.setPins(SS,RST,DIO0);
  Serial.println("LoRa Sender"); 

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  pulsev = analogRead(pulse)/12;
   int xValue = analogRead(xPin);
  tempv = analogRead(temp)/10;
  Serial.print("PULSE=");
  Serial.println(pulsev);
  Serial.print("X-axis: ");
  Serial.println(xValue);
  Serial.print("TEMPERATURE=");
  Serial.println(tempv);
  delay(1000);
  if (pulsev >60 )
  {
    Serial.print("NORMAL PULSE RATE");
    delay(600);
  }
  if (xValue <1023)
  {
    Serial.print("PERSON FALL DOWN");
    delay(600);
  }
  if (tempv <75 )
  {
    Serial.print("LOW TEMPERATURE");
    delay(600);
    digitalWrite(relay,HIGH);
    //delay(1000);
    //digitalWrite(relay,HIGH);
  }
  if (tempv >75)
  {
   // Serial.print("NORMAL TEMPERATURE");
    delay(600);
    digitalWrite(relay,LOW);
    //delay(1000);
    //digitalWrite(relay,HIGH);
  }
 
  String dat = String (pulsev)+":"+ String (xValue)+":"+ String (tempv)+":"+ String (loc)+":"+ String ("");
  LoRa.beginPacket();
  LoRa.println(dat);
  Serial.println(dat);
  LoRa.endPacket();
}