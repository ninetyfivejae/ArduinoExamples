//const int motorPin = 3;
// 
//void setup()
//{
//pinMode(motorPin,OUTPUT);
//}
// 
//void loop()
//{
//digitalWrite(motorPin, HIGH);
//delay(1000);
// 
//digitalWrite(motorPin,LOW);
//delay(10000);
//}



void setup() {
  pinMode( 6 , OUTPUT);
}
 
void loop() {
  
  analogWrite( 6 , 100 );
  delay(1000);
 
  analogWrite( 6 , 0 );
  delay(3000);
}
