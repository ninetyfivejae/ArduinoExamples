
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(36, PIN, NEO_RGBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  int softpotLeft = analogRead(A0);
  int softpotRight = analogRead(A1);

//  int softpotLeft = map(analogRead(A0),0,1023,0,50);
//  int softpotRight = map(analogRead(A1),0,1023,0,50);
//  int ledReading = map(analogRead(PIN),0,1023,0,50);
//  int a0 = softpotLeft / 10;
//  int a1 = softpotLeft % 10;
//  int b0 = softpotRight / 10;
//  int b1 = softpotRight % 10;
//  int c0 = ledReading / 10;
//  int c1 = ledReading % 10;
//  Serial.print((String)a0 + "." + String(a1) + "   ");
//  Serial.print((String)b0 + "." + String(b1) + "   ");
//  Serial.println((String)c0 + "." + String(c1));
  
  boolean touchedLeft = false;
  boolean touchedRight = false;

  Serial.print(softpotLeft);
  Serial.print("   ");
  Serial.println(softpotRight);

  if (softpotLeft < 990 || softpotLeft > 1020){
    touchedLeft = true;
  }
  else{
    touchedLeft = false;
  }

  if (softpotRight < 990 || softpotRight > 1020){
    touchedRight = true;
  }
  else{
    touchedRight = false;
  }

  SetLeftLight(softpotLeft, touchedLeft);
  SetRightLight(softpotRight, touchedRight);

}

void SetLeftLight(int softpotReading, boolean touched){
  
   if(touched){
    
    if(softpotReading < 256){
      for(int i=0;i<4;i++){
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
    }
    else if(softpotReading >= 256 && softpotReading < 512){
      for(int i=4;i<9;i++){
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
    }
    else if(softpotReading >= 512 && softpotReading < 768){
      for(int i=9;i<14;i++){
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
    }
    else{
      for(int i=14;i<18;i++){
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
    }
  }
  
  else{
    for(int i=0;i<18;i++){
        strip.setPixelColor(i,0,0,0,0);
        strip.show();
    }
  }
  
}

void SetRightLight(int softpotReading, boolean touched){

   if(touched){
    
    if(softpotReading < 256){
      for(int i=32;i<36;i++){
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
    }
    else if(softpotReading >= 256 && softpotReading < 512){
      for(int i=27;i<32;i++){
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
    }
    else if(softpotReading >= 512 && softpotReading < 768){
      for(int i=22;i<27;i++){
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
    }
    else{
      for(int i=18;i<22;i++){
          strip.setPixelColor(i,255,0,0,0);
          strip.show();
      }
    }
  }
  
  else{
    for(int i=18;i<36;i++){
        strip.setPixelColor(i,0,0,0,0);
        strip.show();
    }
  }
  
}

