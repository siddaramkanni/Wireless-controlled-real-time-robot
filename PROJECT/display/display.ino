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
    tft.setTextColor(CYAN, BLACK);
    tft.setTextSize(2.5);     // System font is 8 pixels.  ht = 8*2=16 
    tft.setCursor(75, 0); //100,0
    tft.print("SENSOR OUTPUTS");
   // tft.drawLine(75,17,240,17,WHITE);

      tft.setTextColor(WHITE, BLACK);
    tft.setTextSize(2);     // System font is 8 pixels.  ht = 8*2=16 
    tft.setCursor(3,50); //100,0
    tft.print("Distance in cm     ");

    tft.setCursor(3,90); //100,0
    tft.print("Humans Detected    ");

    tft.setCursor(3,130); //100,0
    tft.print("Explosives Detected");
    
    tft.setCursor(3,170); //100,0
    tft.print("Poisonous Gas      ");
    
  //  tft.drawRect(0,50,155,50,RED);
    //tft.drawRect(155,50,160,50,RED);

 //  tft.drawRect(0,90,155,90,RED);
    //tft.drawRect(157,80,160,80,RED);

     //tft.drawRect(0,100,155,100,RED);
    //tft.drawRect(157,100,160,100,RED);

}

void loop()
{
   tft.setTextSize(2);
  tft.setCursor(250,50);
  tft.setTextColor(GREEN, BLACK);
  tft.print("12.5  ");
    
   tft.setTextSize(2);
  tft.setTextColor(GREEN, BLACK);
  tft.setCursor(250,90);
  tft.print("No     ");
  
 
  while(1)
  {
    tft.setTextSize(2);
   tft.setTextColor(YELLOW, BLACK);
    tft.setCursor(250,130);
  tft.print("Yes ");
  delay(300);
    tft.setTextSize(2);
   tft.setTextColor(RED, BLACK);
    tft.setCursor(250,130);
  tft.print("Yes ");
  delay(300);
  }
  
    tft.setTextSize(2);
   tft.setCursor(250,170);
  tft.setTextColor(GREEN, BLACK);
  tft.print("No  ");

  
  
   // delay(200);
   
}
