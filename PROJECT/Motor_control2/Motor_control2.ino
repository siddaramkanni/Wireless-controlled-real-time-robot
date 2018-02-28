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
int i;
int gENA = 4;
int LEDpin = 42 ;

int automatic = 0;
int manual = 1;
int gun = 52;
int gungnd = 53;

int gunmotorPin1 = 41;
int gunmotorPin2 = 43;

//int LDRPin = A8; // select the input pin for ldr
//int LDRValue = 0;// variable to store the value coming from the sensor


int x;



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
  myservo.attach(5);
 Serial.begin(9600);
  pinMode(gun, OUTPUT);
  pinMode(gungnd, OUTPUT);
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
digitalWrite(gungnd, LOW);
digitalWrite(gun, LOW);
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
            digitalWrite(gun, LOW);
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
            digitalWrite(gun, LOW);
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
            digitalWrite(gun, LOW);
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
            digitalWrite(gun, LOW);
           Serial.print(F("\nLEFT"));
            for (speedcntrl = PS3.getAnalogHat(LeftHatX); speedcntrl > 0; speedcntrl--) {
            analogWrite(ENA, 256 - speedcntrl); analogWrite(ENB, 256 - speedcntrl);
            
           }
            digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);           digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
           }
    }

  }



       if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(TRIANGLE)) {
        digitalWrite(gun, LOW);
        Serial.print(F("\r\nTraingle"));
        PS3.setRumbleOn(RumbleLow);
      }
      if (PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        digitalWrite(gun, LOW);
      }
      if (PS3.getButtonClick(CROSS)) {
        digitalWrite(gun, LOW);
        PS3.setRumbleOn(RumbleLow);
        delay(40);
        PS3.setRumbleOff();
        digitalWrite(gun, HIGH);
        delay(80);
         digitalWrite(gun, LOW);
        delay(80);
         digitalWrite(gun, HIGH);
        delay(80);
         digitalWrite(gun, LOW);
        Serial.print(F("\r\nCrosss"));
      }
      if (PS3.getButtonClick(SQUARE)) {
        digitalWrite(gun, LOW);
        Serial.print(F("\r\nSquare"));
        lightbutton++;
      }
      
        if (PS3.getButtonClick(R1)) {
          digitalWrite(gun, LOW);
        Serial.print(F("\r\nR1"));
        automatic = 1;
        manual = 0;
        }

          if (PS3.getButtonClick(L1)) {
            digitalWrite(gun, LOW);
        Serial.print(F("\r\nL1"));
        manual = 1;
        automatic = 0;
        }

        if (PS3.getButtonClick(DOWN)) {
          digitalWrite(gun, LOW);
       Serial.print(F("\r\nUp"));
        pos = pos + 20;
       myservo.write(pos);              
        delay(15); 
        Serial.println(pos);

         if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED4);
        }
        
      }
      
       if (PS3.getButtonClick(UP)) {
        digitalWrite(gun, LOW);
        Serial.print(F("\r\nDown"));
       pos = pos - 20;
        myservo.write(pos);              
        delay(15);  
        Serial.println(pos);                   
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED2);
        }
      }
 
        if (manual == 1 && PS3.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nmanual Right"));
        
         for(i = 0; i < 1000; i++){
         
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

       if (manual == 1 && PS3.getButtonClick(LEFT)) {
        Serial.print(F("\r\nmanual Left"));
        
        for(i = 0; i<1000; i++){
         
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

    }
      
     
  
  


if (lightbutton%2 == 0) {
    digitalWrite(LEDpin,HIGH);
  }
  else if(lightbutton%2 != 0) {
    digitalWrite(LEDpin,LOW);
  }

  if (automatic == 1 && x == 4 ) {
    Serial.println("BACK");
    for(i = 0; i < 8000; i++){
         
        digitalWrite(gunmotorPin2,HIGH);
        digitalWrite(gunmotorPin1,LOW);
        analogWrite(gENA,255);
        }
        delay(600);
         for(i = 0; i < 8000; i++){
        digitalWrite(gunmotorPin1,HIGH);
        digitalWrite(gunmotorPin2,LOW);
         }
  }
    if (automatic == 1 && x == 3 ) {
      Serial.println("RIGHT");
    for(i = 0; i < 4000; i++){
         
        digitalWrite(gunmotorPin2,HIGH);
        digitalWrite(gunmotorPin1,LOW);
        analogWrite(gENA,255);
        }
        
          delay(600);
         for(i = 0; i < 4000; i++){
        digitalWrite(gunmotorPin1,HIGH);
        digitalWrite(gunmotorPin2,LOW);
         }
  }
    if (automatic == 1 && x == 2) {
        Serial.println("LEFT");
    for(i = 0; i < 4000; i++){
       
        digitalWrite(gunmotorPin2,LOW);
        digitalWrite(gunmotorPin1,HIGH);
        analogWrite(gENA,255);
        }
          delay(600);
         for(i = 0; i < 4000; i++){
        digitalWrite(gunmotorPin2,HIGH);
        digitalWrite(gunmotorPin1,LOW);
         }
  }

if (pos > 180) {
  pos = 180;
}
else if (pos < 0) {
  pos = 0;
}
digitalWrite(gun, LOW);
  }
    








    






        

