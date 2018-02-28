#include <Adafruit_GFX.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <UTFTGLUE.h>              // class methods are in here
UTFTGLUE myGLCD(0x0154,A2,A1,A3,A4,A0);

// Declare which fonts we will be using
#if !defined(SmallFont)
extern uint8_t SmallFont[];    //.kbv GLUE defines as GFXFont ref
#endif
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// work in line numbers.  Font height in ht
int16_t ht = 16, top = 3, line, lines = 15, scroll;
 
void setup()
{
    tft.reset();
   uint16_t id = tft.readID();
    tft.begin(id);
    tft.setRotation(1);     //Landscape
    tft.fillScreen(BLACK);
 /*   tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(3.5);     // System font is 8 pixels.  ht = 8*2=16 
    tft.setCursor(40, 0); //100,0
    tft.print("MILITARY ROBOT");
   //tft.drawLine(75,17,240,17,WHITE);

      tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(2);     // System font is 8 pixels.  ht = 8*2=16 
    tft.setCursor(3,50); //100,0
    tft.print("Distance in cm     ");

    tft.setCursor(3,90); //100,0
    tft.print("Humans Detected    ");

    tft.setCursor(3,130); //100,0
    tft.print("Explosives Detected");
    
    tft.setCursor(3,170); //100,0
    tft.print("Poisonous Gas      ");*/
    
  //  tft.drawRect(0,50,155,50,RED);
    //tft.drawRect(155,50,160,50,RED);

 //  tft.drawRect(0,90,155,90,RED);
    //tft.drawRect(157,80,160,80,RED);

     //tft.drawRect(0,100,155,100,RED);
    //tft.drawRect(157,100,160,100,RED);

}

void loop()
{
  
 info();
 delay(5000);
 tft.fillScreen(BLACK);
 details();
 delay(5000);
 tft.fillScreen(BLACK);
  
 

  
  
   // delay(200);
   
}

void info () {
    
    tft.setTextColor(GREEN, BLACK);
    tft.setTextSize(3.5);     // System font is 8 pixels.  ht = 8*2=16 
    tft.setCursor(40, 0); //100,0
    tft.print("MILITARY ROBOT");

    tft.setTextColor(CYAN, BLACK);
    tft.setTextSize(2);     // System font is 8 pixels.  ht = 8*2=16 
    tft.setCursor(10,50); //100,0
    tft.print("Project by :     ");

    tft.setTextColor(WHITE, BLACK);
    tft.setCursor(40,90); //100,0
    tft.print("Ramachandra Thirtha K   ");

    tft.setCursor(40,130); //100,0
    tft.print("Siddaram G Kanni");
    
    tft.setCursor(40,170); //100,0
    tft.print("Sunil N M     ");

    tft.setCursor(40,210); //100,0
    tft.print("Vandith N Kolambe     ");
}

void details() {
   tft.setTextColor(GREEN, BLACK);
    tft.setTextSize(2.5);   
    tft.setTextColor(WHITE, BLACK);
    tft.setCursor(30,90); //100,0
    tft.print("Manual Control of Robot  ");
    tft.setCursor(30,120);
    tft.print("and Artillary System");

}

