#include<LiquidCrystal.h>       // beacause we using lcd so we need that library
#include <BlynkSimpleStream.h>  // Device push data to blynk app so i need it .

BlynkTimer timer;           // push data like an event after a mount of time we using Blynktimer
WidgetLCD blynklcd (V1);    // define which port we push data in blynk 

char auth[] = "9CzrKOxgkJiHLD1bLA4Nc1tg8cl5usTc"; // using to connect to server and blynk project

const int rs =12, en =11, d4 = 5, d5 = 4, d6 = 3 , d7 = 2; 
const int aqsensor = A0;

LiquidCrystal lcd(rs,en , d4, d5, d6, d7); // define lcd port

void pushData(){                          // using to push data to blynk app
  int pmm = analogRead(A0);               // read values of MQ135 sensor 
  
  blynklcd.print(0,0,"Air Quality: ");
  blynklcd.print(13,0, pmm);
  // if pmm are high enough send a warning message to user
   if(pmm > 300)
  {
    blynklcd.print(0,1, "AQ level :Danger");
  }else{
    blynklcd.print(0,1,"AQ level :Good");
  }
  Blynk.virtualWrite(V1, millis()/1000);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(aqsensor, INPUT);
  Serial.begin(9600);
  Blynk.begin(Serial,auth);

  // Define what lcd we are used
  lcd.begin(16,2);
  lcd.clear(); 
  // send data in a mount of time 
  timer.setInterval(2000L,pushData); 
}

void loop() {
//clear the cld for new message
  lcd.clear();
// reading data of MQ135
  int pmm = analogRead(A0);
  // send message to lcd in blynk
  blynklcd.print(0,0,"Air Quality: ");
  blynklcd.print(13,0, pmm);
  // send message to lcd in device 
  lcd.setCursor(0,0);
  lcd.print ("Air Quality: ");
  lcd.print (pmm);
  lcd.println("");


  if(pmm > 300 )
  {
    lcd.setCursor(0,1);
    lcd.print("AQ level Danger");
  }else{
    lcd.setCursor(0,1);
    lcd.print("AQ level good");
  }
  // start send message to blynk app
  Blynk.run();
  timer.run();
  
  // Wait a few seconds between measurements
  delay(2000);
  blynklcd.clear();
 }
