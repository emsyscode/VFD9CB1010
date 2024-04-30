#include <String.h>
#include <stdlib.h>
//
#include <arduino.h>
#include <SoftwareSerial.h>

#define LED_PIN 13

SoftwareSerial mySerial(11, 10); // RX, TX //Note which I define the pins to be used as TX and RX, you can use the pin 0 & 1 by default!

unsigned long lastTimeLedBlinked = millis();
unsigned long delayBetweenBlink = 2000;
byte ledState = LOW;

void setup() { 
//Serial.begin(9600, SERIAL_8N1);   //Here I send the parameter's

  Serial.begin(115200);  // Initialization of serial to the monitor of IDE
//  while (!Serial)
//  {
//    ; // This waite is necessary only to plataform of LEONARD
//  }
pinMode(LED_PIN, OUTPUT);
pinMode(10, OUTPUT);  //TX  
pinMode(11, INPUT);   //RX

mySerial.begin(9600);
}

void loop() {
//  if (mySerial.available())
//    //Serial.write(mySerial.read());
//  if (Serial.available())
//   // mySerial.write(Serial.read());
uint8_t shift = 0;
uint8_t count = 0;
unsigned long timeNow = millis();
String myStr = String(count, 5); //Here I define the length of string of number, this case put 5 spaces which will be occupied by the number!
String myString = String("Number:  ") + String(myStr);


while(1){
myStr = String(count, 5);
myString = String("Number:  ") + String(myStr);


delay(100);      
timeNow = millis();
//This if is used to make a delay and let the uC not busy or stuck!
  if (timeNow - lastTimeLedBlinked > delayBetweenBlink)
  {
    if (ledState == LOW)
    {
      ledState = HIGH;
      mySerial.print("                                        "); //Send 40 spaces!
    }
    else
    {
      ledState = LOW;
      mySerial.write(0x1b); // 
      mySerial.write(0x40); // mySerial.write(0x44);//Write continuous
      switch (shift){
        case 0: shift++; mySerial.print("012356789ABCDEFGHIJKLMNOPQRSTUVXZW"); 
        break; 
        case 1: shift++; mySerial.write(0x0b); /*Initial cursor*/ mySerial.print(myString);  
        break; 
        case 2: shift=0; mySerial.print("Hi Folks!                               "); 
        break;
      }    
      count++;
    }
    digitalWrite(LED_PIN, ledState);
    lastTimeLedBlinked = timeNow;
  } 
  Serial.println(count);
  }
}
