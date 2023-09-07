#include <Wire.h>
#include <Adafruit_GFX.h>
#include "images.h"

/* SSD1306 OLED setup */
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128                      //OLED display width, in pixels
#define SCREEN_HEIGHT 64                      //OLED display height, in pixels
#define OLED_RESET 16                         //Reset pin - changed to 16 for TTGO board
TwoWire twoWire = TwoWire(1);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &twoWire, OLED_RESET);

/* vars for serial input */
String inputString = "";
boolean stringComplete = false;
    int Serial_eventDelay = 15;

void setup() {

  twoWire.begin(2,15);                        //Needs to come before display.begin() is used
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //Initialize with the I2C addr 0x3C (128x64)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);                                  //Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  
  display.setRotation(0);                     //Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* Text wrapping */
  display.setTextWrap(false);                 //Stop  "Loads/Temps" wrapping and corrupting static characters

  /* Show logo boot */
  display.drawBitmap(0, 0, Loading_bits, Loading_width, Loading_height, 1);
  display.display();

  /* Serial setup, start serial port at 921600 bps and wait for port to open: */
  Serial.begin(115200);
  inputString.reserve(200);
  
  /* Waiting Serial connected */
  while (!Serial.available()) {
    display.fillRect(90, 24, 38, 16, BLACK);
    display.fillRect(64, 31, 32, 2, WHITE);
    display.drawBitmap(96, 16, USB_bits, USB_width, USB_height, 1);
    display.display();
    delay(500);
    display.fillRect(90, 24, 38, 16, BLACK);
    display.drawBitmap(90, 16, USB_bits, USB_width, USB_height, 1);
    display.display();
    delay(300);
  }

  display.clearDisplay();
  
}

void loop() {

  /* Serial stuff */
  serialEvent();

  /* OLED DRAW STATS */
  if (stringComplete) {
    Display();

    inputString = "";
    stringComplete = false;
  }
  
}

void serialEvent() {

    while (Serial.available()) {              //USB Serial Available?
    char inChar = (char)Serial.read();        //Read USB Serial
    
    inputString += inChar;
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption
    }
  }

}
