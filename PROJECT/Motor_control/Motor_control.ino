
 /*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */


int IN1 = 22; //motors IN
int IN2 = 24;    //motors IN
int IN3 = 26;     //motors IN
int IN4 = 28;     //motors IN
int ENA = 2;
int ENB = 3;
int gENA = 4;
float speedcntrl ;
int gunmotorPin1 = 41;
int gunmotorPin2 = 43;
int i;

int LEDpin = 52 ;
int LDRPin = A8; 
int lightbutton, LDRValue;

#include <Servo.h>
Servo myservo;
int pos = 0;

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
 
  Serial.begin(9600); 
  
  pinMode(gENA, OUTPUT);
  pinMode(gunmotorPin1, OUTPUT);
  pinMode(gunmotorPin2, OUTPUT);
  
  myservo.attach(52);
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
  //  Serial.print(PS3.getAnalogHat(LeftHatX));
   //  Serial.print(F("\tLeftHatY: "));
   //  Serial.print(PS3.getAnalogHat(LeftHatY));
   //  delay(300);
    
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
    
            if (/*100 < PS3.getAnalogHat(LeftHatY) < 140 &&*/ PS3.getAnalogHat(LeftHatX) < 137 && PS3.getAnalogButton(R2) == 0 ) {
            digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); 
            digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
            Serial.print(F("\nLEFT"));
            for (speedcntrl = PS3.getAnalogHat(LeftHatX); speedcntrl > 0; speedcntrl--) {
            analogWrite(ENA, 256 - speedcntrl); analogWrite(ENB, 256 - speedcntrl);
            
           }
            digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); 
            digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
           }

          
    

    




    
  
    
    

    // Analog button values can be read from almost all buttons
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
     Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (PS3.PS3Connected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }

    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTraingle"));
        PS3.setRumbleOn(RumbleLow);
      }
      if (PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS3.setRumbleOn(RumbleHigh);
      }
      if (PS3.getButtonClick(CROSS))
        Serial.print(F("\r\nCross"));
      if (PS3.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        lightbutton++;
      }

      if (PS3.getButtonClick(UP)) {
        
        Serial.print(F("\r\nUp"));
       pos = pos + 20;
       myservo.write(pos);              
        delay(15);                        
         
        
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED4);
        }
        
      }
  if (PS3.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight"));
        
        for(i = 0; i<5000; i++){
         
        digitalWrite(gunmotorPin1,HIGH);
        digitalWrite(gunmotorPin2,LOW);
        analogWrite(gENA,255);
        }
        digitalWrite(gunmotorPin1,LOW);
        digitalWrite(gunmotorPin2,LOW);
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED1);
        }
      }
      if (PS3.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
        pos = pos - 20;
        myservo.write(pos);              
        delay(15);                     
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED2);
        }
      }
      if (PS3.getButtonClick(LEFT)) {
        Serial.print(F("\r\nLeft"));
        
         for(i = 0; i < 4000; i++){
         
        digitalWrite(gunmotorPin2,HIGH);
        digitalWrite(gunmotorPin1,LOW);
        analogWrite(gENA,255);
        }
        digitalWrite(gunmotorPin1,LOW);
        digitalWrite(gunmotorPin2,LOW);
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED3);
        }
      }

      if (PS3.getButtonClick(L1))
        Serial.print(F("\r\nL1"));
      if (PS3.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
      if (PS3.getButtonClick(R1))
        Serial.print(F("\r\nR1"));
      if (PS3.getButtonClick(R3))
        Serial.print(F("\r\nR3"));

      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
    }
  }

 LDRValue = analogRead(LDRPin);
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


 if (lightbutton%2 == 0) {
    digitalWrite(LEDpin,HIGH);
  }
  else if(lightbutton%2 != 0) {
    digitalWrite(LEDpin,LOW);
  }
}
}

  
  

