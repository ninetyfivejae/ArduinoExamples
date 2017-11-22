/*#include<SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

int blueTx = 2;
int blueRx = 3;
int softpotLeft;
int softpotRight;

//char alert;
SoftwareSerial mySerial(blueTx, blueRx);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(35, PIN, NEO_RGBW + NEO_KHZ800);

void setup() 
{
  Serial.begin(9600);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);

  mySerial.begin(9600);
  // put your setup code here, to run once:

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  
}

void loop() 
{
  for(int i=0;i<36;i++){
    strip.setPixelColor(i,255,0,0,0);
    strip.show();
  }
  
  softpotLeft = analogRead(A0);
  softpotRight = analogRead(A1);
  
  delay(50);
    
  Serial.print(softpotLeft);
  Serial.print("   ");
  Serial.println(softpotRight);

}
*/

#include<SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

int blueTx = 2;
int blueRx = 3;
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
String myString = "";
char alert;
SoftwareSerial mySerial(blueTx, blueRx);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(36, PIN, NEO_RGBW + NEO_KHZ800);

byte data[] = { B00000000/*좌측6개*/, B00001000/*우측7개*/};

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  mySerial.begin(9600);
  // put your setup code here, to run once:
}

void loop()
{
  int softpotLeft = analogRead(A0);
  int softpotRight = analogRead(A1);
  
  boolean touchedLeft = false;
  boolean touchedRight = false;

  Serial.print(softpotLeft);
  Serial.print("   ");
  Serial.println(softpotRight);

  delay(50);
        
  _595_out();

}

void _595_out()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, data[0]);
  shiftOut(dataPin, clockPin, LSBFIRST, data[1]);
  digitalWrite(latchPin, HIGH);
}
