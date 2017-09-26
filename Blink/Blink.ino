int led1 = 13;
int led2 = 12;
int led3 = 11;
int led4 = 10;
int led5 = 9;

int time = 200;

void setup() {
  for(int i=13;i>8;i--)
  {
    pinMode(i, OUTPUT);
  }
}
 
void loop() {
  for(int i=13;i>8;i--)
  {
    digitalWrite(i, HIGH);
    delay(time);
  }
  
  for(int i=9;i<14;i++)
  {
    digitalWrite(i, LOW);
    delay(time);
  }
}
