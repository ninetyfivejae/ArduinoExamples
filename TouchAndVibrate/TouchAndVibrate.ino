int touchSensor = A0;  // 터치센서 핀 설정
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
  /*
  int touchValue = digitalRead(touchSensor);
   
  if (touchValue == HIGH){      // 터치됨
    digitalWrite(ledPin, HIGH);
    Serial.println("TOUCHED");
    analogWrite( 6 , 100 );
  } else {                      //터치 안됨
    digitalWrite(ledPin,LOW);
    Serial.println("NOT TOUCHED");
  }
  */
  
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
}
