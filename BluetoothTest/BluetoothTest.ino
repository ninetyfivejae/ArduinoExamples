/*int touchSensor = A0;  // 터치센서 핀 설정
int ledPin = 6;       // LED 핀 설정
int motorPin = 6;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
  //pinMode(motorPin, OUTPUT);
  //pinMode(touchSensor, INPUT);
}
 
void loop() {
  
  if (stringComplete)
  {
    if(inputString.equals("danger\n"))
    {
      Serial.print(inputString + " WATCH OUT!!!\n");
      inputString = "";
      stringComplete = false;
      digitalWrite(ledPin, HIGH);
      analogWrite( motorPin , 100 );
      delay(500);
      digitalWrite(ledPin, LOW);
    }
    else
    {
      Serial.print(inputString);
      inputString = "";
      stringComplete = false;
      digitalWrite(ledPin, LOW);
    }    
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}*/





/*
#include<SoftwareSerial.h>
int blueTx = 2;
int blueRx = 3;
SoftwareSerial mySerial(blueTx, blueRx);
String myString = "";

void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop(){
  
  while(mySerial.available()){
    byte myChar = (byte)mySerial.read();
    myString += myChar;
    delay(5);
  }
    
  if(!myString.equals("")){
      Serial.println("input value : " + myString);
      myString = "";
  }

//  while(mySerial.available()){
//    char myChar = (char)mySerial.read();
//    myString += myChar;
//    if(myChar == '\n'){
//      Serial.println("input value : " + myString);
//      myString = "";
//    }
//  }
  
}
*/
















/*
#include<SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define LEFTTOUCH 1
#define RIGHTTOUCH 2

int softpotLeft;
int softpotRight;
int blueRx = 2;
int blueTx = 3;
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

char test; //test for the bluetooth communication
String notification = "";

byte data;

byte touchData[] = { B00000000, B00000000}; //좌 우

SoftwareSerial mySerial(blueRx, blueTx);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(35, PIN, NEO_RGBW + NEO_KHZ800);

void SetVibration(int mode,int softpotReading)
{ 
  if(mode == RIGHTTOUCH) // 오른쪽터치
  {
    if(softpotReading >= 0 && softpotReading < 483)
    {
      touchData[1] = B11000000;
    }
    else if(softpotReading >= 483 && softpotReading < 630)
    {
      touchData[1] = B01100000; 
    }
    else if(softpotReading >= 630 && softpotReading < 768)
    {
      touchData[1] = B00110000;
    }
    else if(softpotReading >= 768 && softpotReading < 902)
    {
      touchData[1] = B00011000;
    }
    else if(softpotReading >= 902 && softpotReading < 972)
    {
      touchData[1] = B00001100;
    }
    else if(softpotReading >= 972 && softpotReading < 1023)
    {
      touchData[1] = B00000110;
    }
  }
  else // 왼쪽터치
  {
      Serial.println(softpotLeft);
    if(softpotReading >= 0 && softpotReading < 508)
    {
      touchData[0] = B00001100;
    }
    else if(softpotReading >= 508 && softpotReading < 663)
    {
       touchData[0] = B00011000;
    }
    else if(softpotReading >= 663 && softpotReading < 788)
    {
      touchData[0] = B00110000;
    }
    else if(softpotReading >= 788 && softpotReading < 920)
    {
      touchData[0] = B01100000;
    }
    else if(softpotReading >= 920 && softpotReading < 985)
    {
      touchData[0] = B11000000;    
    }
    else if(softpotReading >= 985 && softpotReading < 1023)
    {
      touchData[0] = B10000000;
      touchData[1] = touchData[1] | B00000010;
    }
  }
}

void StopVibration()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  digitalWrite(latchPin, HIGH);
}

void StopLight()
{
  for(int i=0; i<35; i++)
  {
      strip.setPixelColor(i,0,0,0,0);
      strip.show();
  }
}

void SetLight(char alert)
{
  switch(alert)
  {
    case '1': // 좌회전
      if(touchData[0] != B10000000)
      {
        touchData[1] = B00000000;
      }
      for(int i=0;i<18;i++)
      {
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
      break;

    case '2': // 우회전
      touchData[0] = B00000000;
      for(int i=17;i<35;i++)
      {
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
      break;

    case '3': // 유턴
      for(int i=0;i<9;i++)
      {
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
      for(int i=26;i<35;i++)
      {
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
      break;

    case '4': // 직진
      for(int i=9;i<26;i++)
      {
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
      break;

    case '5': // 위험감지
      for(int j=0;j<35;j++)
      {
         strip.setPixelColor(j,0,255,0,0);
         strip.show();
      }
      break;
  }
}

void setup() 
{
  mySerial.begin(9600);
  Serial.begin(9600);

  softpotLeft = analogRead(A0);
  softpotRight = analogRead(A1);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{ 
   StopVibration();

   if (mySerial.available()) 
   { 
      softpotLeft = analogRead(A0);
      softpotRight = analogRead(A1);
      delay(10);
      // 수신 받은 데이터 저장
      test = mySerial.read(); 
      // 수신된 데이터 시리얼 모니터로 출력
      //Serial.write(data);
      Serial.println(softpotRight);
      // 수신 받은 데이터를 버퍼에 저장
  
      if (softpotRight < 1002 || softpotRight > 1007 || softpotLeft < 1002 || softpotLeft > 1007)
      { 
         SetVibration(RIGHTTOUCH, softpotRight);
         SetVibration(LEFTTOUCH, softpotLeft);
  
         for(int l=0; l<5; l++)
         {
            SetLight(data);
            digitalWrite(latchPin, LOW);
            shiftOut(dataPin, clockPin, LSBFIRST, touchData[0]);
            shiftOut(dataPin, clockPin, LSBFIRST, touchData[1]);
            digitalWrite(latchPin, HIGH);
            delay(500);
            
            StopVibration();
            delay(100);
         }     
         Serial.println(touchData[0]);
         StopLight();
      }
      
    }
}
*/


/*
//AT+NAME원하는이름
//AT+PIN비밀번호

#include<SoftwareSerial.h>

SoftwareSerial BTSerial(2,3);

void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop(){
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
}
*/






#include<SoftwareSerial.h>

SoftwareSerial BTSerial(2,3);

String meter = "";
String turnType = "";

boolean isTurnType = false;
boolean complete = false;

void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop(){
  
  while(BTSerial.available()){
    //Serial.write(BTSerial.read());
    //Serial.println("//처음");

    char inChar = (char)BTSerial.read();

    if(inChar == ' ')
    {
      isTurnType = true;
    }

    if(isTurnType)
    {
      if(inChar!=' '&&inChar!='.')
      {
         turnType += inChar;
      }
      if(inChar=='.')
      {
        Print();
        meter = "";
        turnType = "";
        isTurnType = false;
        complete =false;
      }
    }
    else
    {
      meter += inChar;
    }
  }
}

void Print(){
  Serial.println(meter);
  Serial.println("//");
  Serial.println(turnType);
}

