/*const int SOUND_SENSOR_PIN = A0;
int sensorValue;
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  sensorValue = analogRead(SOUND_SENSOR_PIN);

  Serial.println(sensorValue);
  delay(100);
  
//  if(sensorValue > 100){
//    Serial.println(sensorValue);
//    delay(100);
//  }
//  else{
//    delay(100);
//  }
}
*/



/*
// 소스코드는 adafruit 의 
// https://learn.adafruit.com/adafruit-microphone-amplifier-breakout?view=all
// 예제에 있는 코드를 사용했습니다.
const int sampleWindow = 30; //샘플링 시간 ms
unsigned int sample;


void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long startMillis = millis(); // 생플링 시작
  unsigned int peakToPeak = 0;   // 음성신호의 진폭

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // 생플링 구간동안 최댓값과 최소값을 읽어들입니다.
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(0);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // 최대값에서 최소값을 빼서 진폭을 계산
  double volts = (peakToPeak * 5.0) / 1024;  // 이를 전압단위로 변경합니다.

  Serial.println(volts);
}*/


// 사운드 센서를 A0번핀에 연결합니다.
int sensorPin = A0; 
// LED를 11번핀에 연결합니다.
int ledPin = 11; 

void setup() {
  // ledPin을 출력으로 설정합니다.
  pinMode(ledPin,OUTPUT);
  //시리얼 통신을 시작합니다.
  Serial.begin(9600); 
}

void loop() {
  // 사운드 센서로부터 MIC 센서값을 읽어 들입니다.
  int value = analogRead(sensorPin); 
  // 읽어들인 MIC 센서의 값을 0~255로 변환합니다.
  int intensity = map(value,0,1024,0,140);
  //ledPin에 변환된 값을 넣어줍니다.
  analogWrite(ledPin, intensity); 
  //센서값을 시리얼 모니터로 출력하여 현재 센서값을 보여줍니다.
  Serial.println(intensity);
  //1000ms 동안 대기
  delay(100);
}
