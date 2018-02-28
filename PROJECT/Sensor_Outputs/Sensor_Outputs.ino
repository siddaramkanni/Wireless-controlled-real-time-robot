
int x = 0;
int y = 0;
int ledPin = 13;
int num = 0;
int ls = 0;
 
int PIRPin1 = 8 ;
int PIRPin2 = 9;
int PIRPin3 = 4;//PIR sensor
int PIRout1;
int PIRout2;
int PIRout3;
int triggerPin = 2;    //Ultrasonic sensor
int echoPin = 3; //Ultrasonic sensor
int distance;
int val;
int tempPin = A2;
int tim;
int sound = 0;

int soundSensor1 = 12;
int soundSensor2 = 13;
int ldrPin = A1;
int ldrval;
int ldrled = 11;



void setup() {
Serial.begin(9600);

  pinMode(PIRPin1, INPUT);
  pinMode(PIRPin2, INPUT);
  pinMode(PIRPin3, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode (tempPin, INPUT);
  pinMode (soundSensor1, INPUT);
  pinMode (soundSensor2, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(ldrled, OUTPUT);
 
}

void loop() {
  int statusSensor1 = digitalRead (soundSensor1);
  int statusSensor2 = digitalRead (soundSensor2);
  ldrval = analogRead(ldrPin);
   

  if (statusSensor1 == 1 || statusSensor2 == 1)
  {
    sound = 1;
  }
  
  else
  {
    sound = 0;
  }


 digitalWrite(triggerPin,LOW);
 delayMicroseconds(2);
 digitalWrite(triggerPin,HIGH);
 delayMicroseconds(10);
 digitalWrite(triggerPin,LOW);
 delayMicroseconds(2);
 tim = pulseIn(echoPin,HIGH);
 distance = tim * 0.034/2;
//Serial.println(statusSensor1);
//Serial.print(statusSensor2);
//Serial.print(statusSensor3);
//Serial.println(distance);
 
  
 val = analogRead(tempPin);
 float m = (val/1024.0)*5000;
 float cel = m/10;
 PIRout1 = digitalRead(PIRPin1);
 PIRout2 = digitalRead(PIRPin2);
 PIRout3 = digitalRead(PIRPin3);

 if(PIRout1 == 1) {
Serial.print(" FRONT");
x = 1;
}
else if(PIRout2 == 1) {
Serial.print(" LEFT");  
x = 2;
}
else if(PIRout3 == 1) {
Serial.print(" RIGHT");
x = 3;  
}
else if(PIRout1 == 0 || PIRout2 == 0 || PIRout3 == 0) {
Serial.print(" NONE");  
}

Serial.print(",");

Serial.print(" ");
Serial.print((float)cel);
Serial.print("C");
Serial.print(",");

Serial.print(" ");
Serial.print(distance);
Serial.print("cm");
Serial.print(",");


if (sound == 1) {
 Serial.print("DETECTED"); 
}
else {
Serial.print("NONE"); 
}
Serial.print(",");


if (sound == 1) {
  if (x == 1) {
   Serial.print(" FROM FRONT");
  }
   else if (x == 2) {
   Serial.print(" FROM LEFT");
  }
   else if (x == 3) {
   Serial.print(" FROM RIGHT");
  }
   else {
   Serial.print(" FROM BACK");
  }

   
  
}
  else {
    y = 0;
    Serial.print("NONE");
  }

Serial.print(",");

if (ldrval < 13) {
  Serial.print("Low");
  ls = 10;
   digitalWrite(ldrled, HIGH);
}
 
else if (ldrval > 120) {
 Serial.print("High"); 
 ls = 5;
 digitalWrite(ldrled, LOW);
}
else if ( 26 < ldrval < 119) {
 Serial.print("Normal"); 
 ls = 5;
 digitalWrite(ldrled, LOW);
 
}

delay(100);
Serial.println(",");





}
