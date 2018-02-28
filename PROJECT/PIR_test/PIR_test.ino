int x = A0;
int ledPin = 13;
int y;
void setup() {
  Serial.begin(9600);
  pinMode(x, OUTPUT);

}

void loop() {
  for(;;) {
  y = analogRead(x);
  Serial.println(y);
  
  if (y!= 0) {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
  }
    else {
      digitalWrite(ledPin, LOW);
    }
  }
  //delay(1000);  

}

