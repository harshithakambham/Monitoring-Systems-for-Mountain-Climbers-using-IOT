#define BLYNK_TEMPLATE_ID "TMPL3ps1jYcd1"
#define BLYNK_TEMPLATE_NAME "mountain"
#define BLYNK_AUTH_TOKEN "CGLRE6C-6FOGI8LpJLI_tdChRYMKYhjf"
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

#include <SPI.h>
#include <LoRa.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27,16,2);
#define SS 15
#define RST 16
#define DIO0 2
const int relay = D3;
String pulse,acc,temp,lati,lon;
float a,b,c,d,e;
String getStringPartByNr(String data, char separator, int index)
{
  int stringdata = 0;
  String datapart ="";
  for (int i=0; i<data.length()-1; i++)
  {
    if(data[i]==separator)
    {
      stringdata++;
    }
    else if (stringdata== index)
    {
      datapart.concat(data[i]);
    }
    else if (stringdata>index)
    {
      return datapart;
      break;
    }
  }
  return datapart;
}
char auth[] = "CGLRE6C-6FOGI8LpJLI_tdChRYMKYhjf";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "iotadmin";
char pass[] = "12345678";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(relay,OUTPUT);
Blynk.begin(auth, ssid, pass);

  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("LIFE JACKET");
  delay(2000);
  lcd.clear();
  while (!Serial);
 LoRa.setPins(SS, RST, DIO0);
  Serial.println("LoRa Receiver");
//  connectWifi();
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
   int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      // Serial.print((char)LoRa.read());
      String rcv = LoRa.readStringUntil('\n');
      Serial.println(rcv);
 String pulse = getStringPartByNr(rcv,':',0);
   String acc = getStringPartByNr(rcv,':',1);
   String temp = getStringPartByNr(rcv,':',2);
   String lati = getStringPartByNr(rcv,':',3);
   String lon = getStringPartByNr(rcv,':',4);
  
float a = pulse.toInt();
    float b = acc.toInt();
    float c = temp.toInt();
    float d = lati.toInt();
    float e = lon.toInt();
     Serial.print("PULSE=");
    Serial.println(a);
    Serial.print("ACCELERATION=");
    Serial.println(b);
    Serial.print("TEMPERATURE=");
    Serial.println(c);
    Serial.print("LATITUDE=");
    Serial.println(d);
    Serial.print("LONGITUDE=");
    Serial.println(e);
    lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("P=");
  lcd.setCursor(2,0);
  lcd.print(a);
  Blynk.virtualWrite(V2," PULSE=");
  Blynk.virtualWrite(V2, a);
  lcd.setCursor(7,0);
  lcd.print("A=");
  lcd.setCursor(9,0);
  lcd.print(b);
  Blynk.virtualWrite(V2," ACCELERATION=" );
  Blynk.virtualWrite(V2, b);
  lcd.setCursor(0,1);
  lcd.print("TEMP=");
  lcd.setCursor(7,1);
  lcd.print(c);
  Blynk.virtualWrite(V2," TEMPERATURE=" );
  Blynk.virtualWrite(V2, c);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LAT=");
  lcd.setCursor(6,0);
  lcd.print(d);
 Blynk.virtualWrite(V2," LATITUDE=");
  Blynk.virtualWrite(V2, d);
  lcd.setCursor(0,1);
  lcd.print("LON=");
  lcd.setCursor(6,1);
  lcd.print(e);
  Blynk.virtualWrite(V2," LONGITUDE=");
  Blynk.virtualWrite(V2, e);
  delay(2000);
  lcd.clear();
  if (a<40 )
  {
    lcd.setCursor(0,0);
  lcd.print("LOW PULSE");
    digitalWrite(relay,HIGH);
    delay(1000);
    digitalWrite(relay,LOW);
    Serial.print("HIGH PULSE RATE");
   Blynk.virtualWrite(V2, "HIGH PULSE RATE");
    delay(600);
  }
  if (b <1023)
  {
    lcd.setCursor(2,0);
  lcd.print("PERSON FALL");
    digitalWrite(relay,HIGH);
    delay(1000);
    digitalWrite(relay,LOW);
    Serial.print("PERSON FALL DOWN");
  Blynk.virtualWrite(V2, " PERSON FALL DOWN");
    delay(600);
  }
  if (c <75)
  {
    lcd.setCursor(0,1);
  lcd.print("LOW TEMPERATURE");
    digitalWrite(relay,HIGH);
    delay(1000);
    digitalWrite(relay,LOW);
    Serial.print("LOW TEMPERATURE");
  Blynk.virtualWrite(V2,"LOW TEMPERATURE");
    delay(600);
  }
    }
  }

  Blynk.run();
}