#include <Wire.h>
int x = 0;
int y = 0;
int ledPin = 13;
int num = 0;
 

int triggerPin = 2;    //Ultrasonic sensor
int echoPin = 3; //Ultrasonic sensor
int distance;
int val;
int tempPin = A2;
int tim;




void setup() {
Serial.begin(9600);
  Wire.begin(8);                
  Wire.onReceive(receiveEvent); 
 
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode (tempPin, INPUT);

}

  void receiveEvent(int howMany) {
  while (1 < Wire.available()) { 
    char c = Wire.read(); 
   Serial.print(c);        
  }
  x = Wire.read(); 
  Serial.println(x); 
  delay(500);          
}

void loop() {

 digitalWrite(triggerPin,LOW);
 delayMicroseconds(2);
 digitalWrite(triggerPin,HIGH);
 delayMicroseconds(10);
 digitalWrite(triggerPin,LOW);
 delayMicroseconds(2);
 tim = pulseIn(echoPin,HIGH);
 distance = tim * 0.034/2;
//Serial.println(distance);
 
  
 val = analogRead(tempPin);
 float m = (val/1024.0)*5000;
 float cel = m/10;

y = x/10;

 if(y == 1) {
Serial.print("FRONT");

}
else if(y == 2) {
  Serial.print("LEFT");

}
else if(y == 3) {
Serial.print("RIGHT");
 
}
else if(y == 0) {
 Serial.print("NONE"); 
}
Serial.print("|");
 if(x == 11) {
Serial.print("THREAT FROM FRONT");

}
else if(x == 22) {
  Serial.print("THREAT FROM LEFT");

}
else if(x == 33) {
Serial.print("THREAT FROM RIGHT");
 
}
else if(x == 04) {
 Serial.print("THREAT FROM BACK"); 
}

Serial.print("|");


//Serial.print((float)cel);
//Serial.print("C");
//Serial.print("|");


//Serial.print(distance);
//Serial.print("cm");
//Serial.print("|");



}
