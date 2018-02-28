int IN1 = 22; //motors IN
int IN2 = 24;    //motors IN
int IN3 = 26;     //motors IN
int IN4 = 28;     //motors IN
int ENA = 2;
int ENB = 3;
float speedcntrl ;
int lightbutton = 1;
int pos = 0;
int val;

int gunmotorPin1 = 41;
int gunmotorPin2 = 43;

//int LDRPin = A8; // select the input pin for ldr
//int LDRValue = 0;// variable to store the value coming from the sensor
int LEDpin = 23 ;




#include <Servo.h>
Servo myservo;


#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;








void setup() {
  myservo.attach(23);
 Serial.begin(9600);
 
  pinMode(LEDpin,OUTPUT);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);

  

  
}


void loop() {

     Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
 //  Serial.print(F("\r\nLeftHatX: "));
   // Serial.print(PS3.getAnalogHat(LeftHatX));
    // Serial.print(F("\tLeftHatY: "));
   //  Serial.print(PS3.getAnalogHat(LeftHatY));
  //   delay(300);
    //   Serial.print(F("\tRightHatX: "));
    //   Serial.print(PS3.getAnalogHat(RightHatX));
    //   Serial.print(F("\tRightHatY: "));
     //  Serial.print(PS3.getAnalogHat(RightHatY));
      
      
    
           if (100 < PS3.getAnalogHat(LeftHatX) < 140 && PS3.getAnalogHat(LeftHatY) < 137 && PS3.getAnalogButton(R2) >= 200) {
            digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
            digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
           Serial.print(F("\nFORWARD"));
            for (speedcntrl = PS3.getAnalogHat(LeftHatY); speedcntrl > 0;speedcntrl-- ) {
            analogWrite(ENA, 256 - speedcntrl); analogWrite(ENB, 256 - speedcntrl);
            
           }
           digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); 
           digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
           }

            if (100 < PS3.getAnalogHat(LeftHatX) < 140 && PS3.getAnalogHat(LeftHatY) > 140 && PS3.getAnalogButton(R2) >= 200 ) {
            digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); 
            digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
            Serial.print(F("\nREVERSE"));
            for (speedcntrl = PS3.getAnalogHat(LeftHatY); speedcntrl <= 255;speedcntrl++ ) {
            analogWrite(ENA, speedcntrl); analogWrite(ENB, speedcntrl);
           
           }
           digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); 
            digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
           }

          if (100 < PS3.getAnalogHat(LeftHatY) < 140 && PS3.getAnalogHat(LeftHatX) > 140 && PS3.getAnalogButton(R2) == 0 ) {
            digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
            digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
            Serial.print(F("\nRIGHT"));
            for (speedcntrl = PS3.getAnalogHat(LeftHatX); speedcntrl <= 255;speedcntrl++ ) {
            analogWrite(ENA, speedcntrl); analogWrite(ENB, speedcntrl);
            
           }
            digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); 
            digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
           }
    
            if (100 < PS3.getAnalogHat(LeftHatY) < 140 && PS3.getAnalogHat(LeftHatX) < 137 && PS3.getAnalogButton(R2) == 0 ) {
            digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); 
            digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
           Serial.print(F("\nLEFT"));
            for (speedcntrl = PS3.getAnalogHat(LeftHatX); speedcntrl > 0; speedcntrl--) {
            analogWrite(ENA, 256 - speedcntrl); analogWrite(ENB, 256 - speedcntrl);
            
           }
            digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); 
            digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
           }
          if( PS3.getAnalogHat(RightHatX) > 200 && PS3.getAnalogButton(L2) < 60) {
           digitalWrite(gunmotorPin1, LOW); digitalWrite(gunmotorPin2, HIGH); 
           
           }
           if( PS3.getAnalogHat(RightHatX) < 50 && PS3.getAnalogButton(L2) < 60) {
           digitalWrite(gunmotorPin1, HIGH); digitalWrite(gunmotorPin2, LOW); 
           
           }
           
      /*     if( PS3.getAnalogHat(RightHatY) < 50  && PS3.getAnalogButton(L2) > 200) {
            for (pos = 0; pos <= 90; pos += 1) { 
            if( PS3.getAnalogHat(RightHatY) < 50  && PS3.getAnalogButton(L2) > 200) {
            myservo.write(pos); 
            delay(20);            
            }
            else {
              pos = 91;
            }
            //delay(10);                    
             }
           
           }
           if( PS3.getAnalogHat(RightHatY) > 200 && PS3.getAnalogButton(L2) > 200) {
          for (pos = 90; pos > 0; pos -= 1) { 
            if( PS3.getAnalogHat(RightHatY) < 50  && PS3.getAnalogButton(L2) > 200) {
            myservo.write(pos); 
            delay(20);            
            }
            else {
              pos = 0;
            }
            //delay(10);                    
             }         
          //delay(10);                     
         }
         */
         

        if (PS3.getButtonClick(UP)) {
       Serial.print(F("\r\nUp"));
       lightbutton++;
      }
       if(PS3.getAnalogButton(L2)) {
      if(PS3.getAnalogButton(L2)> 75){
        val = PS3.getAnalogButton(L2) - 75;
         myservo.write(val); 
         Serial.println(PS3.getAnalogButton(L2));
      }

       }
  }
  
 /* LDRValue = analogRead(LDRPin);
if(LDRValue<10)
{
  digitalWrite(LEDpin,HIGH);
  delay(100);
}
else
{
  digitalWrite(LEDpin,LOW);
  delay(100);
}
*/
}
if (lightbutton%2 == 0) {
    digitalWrite(LEDpin,HIGH);
  }
  else if(lightbutton%2 != 0) {
    digitalWrite(LEDpin,LOW);
  }
}
    








    






        

