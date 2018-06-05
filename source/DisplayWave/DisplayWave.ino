
#include <PxMatrix.h>

// Pins for LED MATRIX
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_E 0
#define P_OE 2

PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D,P_E);

// Some standard colors
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);

uint16_t myCOLORS[8]={myRED,myGREEN,myBLUE,myWHITE,myYELLOW,myCYAN,myMAGENTA,myBLACK};

#include <Ticker.h>
Ticker display_ticker;
uint8_t display_draw_time = 0;
unsigned long previousMillis = 0;
const float pi = 3.14159;
const int circleDeg = 360;
const int centerY = 15;

uint16_t sinX;
uint8_t  xPos;
uint8_t  yPos;


void drawWave() {
  unsigned long currentMillis = millis();
  uint8_t dotSpeed = 50; // in ms, lower is faster
  uint8_t frequency = 16; // 8, 16 have good effects
  uint8_t amplitude = 2;
  uint8_t maxWidth = 64;
  long elapsed = currentMillis - previousMillis;

  display.drawPixel(xPos,yPos,myGREEN);
  
  if (elapsed >= dotSpeed) {
    previousMillis = currentMillis;
  
    sinX += frequency;
    if (sinX > circleDeg) {
      sinX = 0;
    }
  
    xPos += 1;
    if (xPos > maxWidth) {
      xPos = 0;
    }
    float rad = ( (sinX * pi) / 180 );
    yPos = int((sin(rad) * centerY) / amplitude) + centerY;
  } 
}

// ISR for display refresh
void display_updater() {
  display.display(display_draw_time);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sinX = 0;
  xPos = 0;
  
  // Define your display layout here, e.g. 1/8 step
  display.begin(16);
  
  display_ticker.attach(0.002, display_updater);
  display.clearDisplay();

}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  drawWave();

}
