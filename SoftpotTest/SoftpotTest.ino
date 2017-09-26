/*int softpotPin = 8; //analog pin 0

void setup(){
  //digitalWrite(softpotPin, HIGH); //enable pullup resistor
  Serial.begin(9600);
  pinMode(softpotPin, INPUT);
}

void loop(){
  //int softpotReading = analogRead(softpotPin);
  int touchValue = digitalRead(softpotPin);

  if(touchValue == HIGH){
    Serial.println("TOUCHED");
  }
  else{
    Serial.println("NOT TOUCHED");
  }
  
  //double value = map(softpotReading, 0,1024,0,10000000);

  delay(200);
}
*/


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(35, PIN, NEO_RGBW + NEO_KHZ800);



void setup() {
  Serial.begin(9600);
  digitalWrite(A0, HIGH);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  int softpotReading = analogRead(A0);
  
//  int softpotLeft = map(analogRead(A0),0,1023,0,50);
//  int a0 = softpotLeft / 10;
//  int a1 = softpotLeft % 10;
//  Serial.println((String)a0 + "." + String(a1));
  
  boolean touched = false;
  
  if (softpotReading < 990 || softpotReading > 1020){
    touched = true;
  }
  else{
    touched = false;
  }

  if(touched){
    Serial.print("TOUCHED --- ");
    Serial.println(softpotReading);
  }
  else{
    Serial.print("NOT TOUCHED --- ");
    Serial.println(softpotReading);
  }

   if(touched){
    Serial.print("TOUCHED --- ");
    Serial.println(softpotReading);

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
    Serial.print("NOT TOUCHED --- ");
    Serial.println(softpotReading);

    for(int i=0;i<18;i++){
        strip.setPixelColor(i,0,0,0,0);
        strip.show();
    }
  }

}



