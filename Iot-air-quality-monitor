// we using proteus + blynk to simulate

#include "DHT.h"                //library dth.h help we can using dth sensor 
#include<LiquidCrystal.h>       // beacause we using lcd so we need that library
#include <BlynkSimpleStream.h>  // Device push data to blynk app so i need it .
#include <SoftwareSerial.h>;

#define DHTTYPE DHT11       // define type of DTH sensor using
#define DHTPIN 8            // pin DTH sensor connect to 
DHT dht(DHTPIN, DHTTYPE);   // Define dth

BlynkTimer timer;           // push data like an event after a mount of time we using Blynktimer
WidgetLCD blynklcd (V1);    // define which port we push data in blynk 

char auth[] = "9CzrKOxgkJiHLD1bLA4Nc1tg8cl5usTc"; // using to connect to server and blynk project

const int rs =12, en =11, d4 = 5, d5 = 4, d6 = 3 , d7 = 2; 
const int aqsensor = A0;
int led = 6;
int buz =7;

LiquidCrystal lcd(rs,en , d4, d5, d6, d7); // define lcd port

void pushData(){                          // using to push data to blynk app
  int pmm = analogRead(A0);               // read values of MQ135 sensor 
  float h = dht.readHumidity();           // read humidity 
  float t = dht.readTemperature();        // read temperature
  
  blynklcd.print(0,0,"Air Quality: ");
  blynklcd.print(13,0, pmm);
  // if pmm and tempareture are high enought send a warning message to user
   if(pmm > 300 || t >=40)
  {
    blynklcd.print(0,1, "AQ level : Danger");
  }else{
    blynklcd.print(0,1,"AQ level : Good");
  }

  // we using vituralWrite to push data to blynk app
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t); 
  Blynk.virtualWrite(V1, millis()/1000);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(led , OUTPUT);
  pinMode(buz ,OUTPUT);
  pinMode(aqsensor, INPUT);
  Serial.begin(9600);
  Blynk.begin(Serial,auth);

  // Define what lcd we are used
  lcd.begin(20,4);
  lcd.clear();
  //start dht sensor
  dht.begin(); 
  // send data in a mount of time 
  timer.setInterval(2000L,pushData); 
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    lcd.clear();
    lcd.setCursor(10,2);
    lcd.print("ERROR dth!!!");
    return;
  }
  
  int pmm = analogRead(A0);
  // send message to lcd in blynk
  blynklcd.print(0,0,"Air Quality: ");
  blynklcd.print(13,0, pmm);
  // send message to lcd in device 
  lcd.setCursor(0,0);
  lcd.print ("Air Quality: ");
  lcd.print (pmm);
  lcd.println("");

  lcd.setCursor(0,2);
  lcd.print("Humidity: " );
  lcd.print(h);
  lcd.print("%");
  
  lcd.setCursor(0,1);
  lcd.print("Temperature: "  );
  lcd.print(t);
  lcd.print("*C");
  

  if(pmm > 300 || t >= 40)
  {
    lcd.setCursor(0,3);
    lcd.print("AQ level Danger");
    tone(buz,1000,200);         
    digitalWrite(led,HIGH);
    
  }else{
    lcd.setCursor(0,3);
    lcd.print("AQ level good");
    noTone(buz);
    digitalWrite(led,LOW);
  }
  // start send message to blynk app
  Blynk.run();
  timer.run();
  
  // Wait a few seconds between measurements
  delay(2000);
  blynklcd.clear();
 }


 
