int PIRPin1 = 4;
int PIRPin2 = 5;
int PIRPin3 = 6;//PIR sensor
int PIRout1;
int PIRout2;
int PIRout3;
int triggerPin = 2;    //Ultrasonic sensor
int echoPin = 3; //Ultrasonic sensor
int distance;

  

int tim;

#include <SoftwareSerial.h>
SoftwareSerial BTserial(0, 1); // RX | TX


int distancemeasure() {

  
  digitalWrite(triggerPin,LOW);
 delayMicroseconds(2);
 digitalWrite(triggerPin,HIGH);
 delayMicroseconds(10);
 digitalWrite(triggerPin,LOW);
 delayMicroseconds(2);
 tim = pulseIn(echoPin,HIGH);
 
 distance = tim * 0.034/2;

}




void setup() {
   BTserial.begin(9600);
  pinMode(PIRPin1, INPUT);
  pinMode(PIRPin2, INPUT);
  pinMode(PIRPin3, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);

}

void loop() {
 distancemeasure();
 digitalWrite(13, HIGH);
 PIRout1 = digitalRead(PIRPin1);
 PIRout2 = digitalRead(PIRPin2);
 PIRout3 = digitalRead(PIRPin3);

  //IMPORTANT: The complete String has to be of the Form: 1234,1234,1234,1234;

//(every Value has to be seperated through a comma (',') and the message has to

//end with a semikolon (';'))
BTserial.print("distance");
BTserial.print("|");
/*if(PIRout1 == 1) {
BTserial.print("FRONT");
}
else if(PIRout2 == 1) {
BTserial.print("LEFT");  
}
else if(PIRout3 == 1) {
BTserial.print("RIGHT");  
}
else if(PIRout1 == 0 || PIRout2 == 0 || PIRout3 == 0) {
BTserial.print("NONE");  
}
*/
BTserial.print(";");
//message to the receiving device
delay(100);




}
