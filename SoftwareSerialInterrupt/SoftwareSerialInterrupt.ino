/*#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX)
SoftwareSerial BTSerial(2, 3); 
// 데이터를 수신 받을 버퍼
byte buffer[1024];
// 버퍼에 데이타를 저장할 때 기록할 위치
int bufferPosition; 

void setup() {
  BTSerial.begin(9600); 
  Serial.begin(9600); 
  // 버퍼 위치 초기화
  bufferPosition = 0; 
}

void loop() {
  // 블루투스로 데이터 수신
  if (BTSerial.available()) { 
    // 수신 받은 데이터 저장
    byte data = BTSerial.read(); 
    // 수신된 데이터 시리얼 모니터로 출력
    Serial.write(data); 
    // 수신 받은 데이터를 버퍼에 저장
    buffer[bufferPosition++] = data; 
    
    // 문자열 종료 표시
    if (data == '\n') { 
      buffer[bufferPosition] = '\0';
      
      // 스마트폰으로 문자열 전송
      BTSerial.write(buffer, bufferPosition);
      bufferPosition = 0;
    }  
  }
}*/









#include<SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

//#ifdef __AVR__
//  #include <avr/power.h>
//#endif

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
int i;
int j;

String myString = "";
//char alert;
byte data;
byte touchData[] = { B00000000/*우측5개*/, B00000000/*좌측8개*/};

SoftwareSerial mySerial(blueRx, blueTx);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(35, PIN, NEO_RGBW + NEO_KHZ800);

void SetVibration(int mode,int softpotReading)
{
  digitalWrite(latchPin, LOW);
  
  if(mode == RIGHTTOUCH) // 오른쪽터치
  {
    if(softpotReading >= 0 && softpotReading < 300)
    {
      touchData[0] = B00000000;
      touchData[1] = B11000000; 
    }
    else if(softpotReading >= 301 && softpotReading < 490)
    {
      touchData[0] = B00000000;
      touchData[1] = B11100000; 
    }
    else if(softpotReading >= 491 && softpotReading < 635)
    {
      touchData[0] = B00000000;
      touchData[1] = B01110000;
    }
    else if(softpotReading >= 636 && softpotReading < 770)
    {
      touchData[0] = B00000000;
      touchData[1] = B00111000;
    }
    else if(softpotReading >= 771 && softpotReading < 860)
    {
      touchData[0] = B00000000;
      touchData[1] = B00011100;
    }
    else if(softpotReading >= 861 && softpotReading < 1023)
    {
      touchData[0] = B00000000;
      touchData[1] = B00001110;
    }
  }
  else // 왼쪽터치
  {
    
  }
  
  shiftOut(dataPin, clockPin, MSBFIRST, touchData[0]);
  shiftOut(dataPin, clockPin, LSBFIRST, touchData[1]);
  digitalWrite(latchPin, HIGH);
}

void StopVibration()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
  shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  digitalWrite(latchPin, HIGH);
}

void StopLight()
{
  for(i=0; i<35; i++)
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
      for(i=0;i<18;i++)
      {
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
      break;

    case '2': // 우회전
      for(i=17;i<35;i++)
      {
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
      break;

    case '3': // 유턴
      for(i=0;i<9;i++)
      {
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
      for(i=27;i<35;i++)
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
      for(j=0;j<36;j++)
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
   if (mySerial.available()) 
   { 
      softpotLeft = analogRead(A0);
      softpotRight = analogRead(A1);
      delay(10);
      // 수신 받은 데이터 저장
      data = mySerial.read(); 
      // 수신된 데이터 시리얼 모니터로 출력
      Serial.write(data);
      Serial.println(softpotRight);
      // 수신 받은 데이터를 버퍼에 저장
  
      if (softpotLeft < 990 || softpotLeft > 1020)
      {
        // 왼쪽 잡았을 때
      }
  
      if (softpotRight < 990 || softpotRight > 1020)
      {
         //오른쪽 잡았을 때
         for(i=0; i<6; i++)
         {
            SetVibration(RIGHTTOUCH, softpotRight);
            SetLight(data);
            delay(500);
            StopVibration();
            StopLight();
            delay(100);
         }      
      }
    }
}
