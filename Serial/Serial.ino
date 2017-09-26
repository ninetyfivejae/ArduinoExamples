void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    int swt = (int)Serial.read();
    if(swt == 49)
    {
      digitalWrite(13, HIGH);
      delay(1000);
    }
    else
    {
      digitalWrite(13, LOW);
      delay(1000);
    }
  }
}
