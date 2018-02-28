#include <Wire.h>
int x;
void setup() {
  Wire.begin(8);                
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600);           
}

void loop() {
  
  while (x == 10) {
//  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); 
  //digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  }
}


void receiveEvent(int howMany) {
  while (1 < Wire.available()) { 
    char c = Wire.read(); 
   Serial.print(c);        
  }
  x = Wire.read();  
   Serial.print(x);            
}
