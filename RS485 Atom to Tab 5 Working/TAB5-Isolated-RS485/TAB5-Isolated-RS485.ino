#include <M5Unified.h>
#include <M5GFX.h>

// Fonts
#include "NotoSansBold15.h"
#include "tinyFont.h"
#include "smallFont.h"
#include "middleFont.h"
#include "bigFont.h"
#include "font18.h"

// Button dimensions 
const int BUTTON_WIDTH = 220;
const int BUTTON_HEIGHT = 80;
const int BUTTON_RADIUS = 6;

// Button positions - evenly spaced near top middle
const int BUTTON_Y = 18;
const int BUTTON_SPACING = 40;
const int TOTAL_BUTTONS_WIDTH = (3 * BUTTON_WIDTH) + (2 * BUTTON_SPACING);
const int BUTTON_START_X = (1280 - TOTAL_BUTTONS_WIDTH) / 2;

// Button coordinates
const int BUTTON1_X = BUTTON_START_X;
const int BUTTON2_X = BUTTON_START_X + BUTTON_WIDTH + BUTTON_SPACING;
const int BUTTON3_X = BUTTON_START_X + 2 * (BUTTON_WIDTH + BUTTON_SPACING);

// Pre-Defined Colours - It uses the slightly odd "16-bit RGB565 color format" 
// https://rgbcolorpicker.com/565
const unsigned short PINK_COLOR = 0xb9f2;  // Pink-ish or RGB (23,15,18) 
const unsigned short BLUE_COLOR = 0x3af8;  // Blue-ish or RGB (7,23,24)
const unsigned short GREEN_COLOR = 0x4607;  // Green-ish or RGB (8,48,7)
const unsigned short YELLOW_COLOR = 0xefa1;  // Yellow-ish or RGB (29,61,1)
const unsigned short RED_COLOR = 0xe904;  // Red-ish or RGB (29,8,4)
const unsigned short WHITE_COLOR = 0xffff;  // White or RGB (31,63,31)
const unsigned short ORANGE_COLOR = 0xfde1;  // Orange-ish or RGB (31,47,1)
const unsigned short BLACK_COLOR = 0x0000;  // Black or RGB (0,0,0)
const unsigned short BACKGROUND_COLOR = 0x10E4; // Dark Blue/Black or RGB (2,7,4)
const unsigned short BACKGROUND_COLOR_BLACK = 0x0000;  // Black or RGB (0,0,0)

int brightness = 125;
bool deb = 0;

// RS485 variables
String rs485_str = "";

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  
  M5.Display.setRotation(3);
  Serial.begin(115200);
  
  // Initialize Serial2 for RS485 communication on GPIO54 (TX) and GPIO53 (RX)
  Serial2.begin(115200, SERIAL_8N1, 54, 53);
  Serial.println("TAB5 RS485 Communication Ready");

  M5.Speaker.setVolume(128);

  // Draw UI
  M5.Display.setTextColor(TFT_WHITE);
  M5.Display.fillScreen(BACKGROUND_COLOR_BLACK);
  drawButtons();
}

void drawButtons() {
  M5.Display.loadFont(bigFont);
  
  // Button 1 - String 1
  M5.Display.fillRoundRect(BUTTON1_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_RADIUS, ORANGE_COLOR);
  M5.Display.setTextColor(BLACK_COLOR, ORANGE_COLOR);
  M5.Display.setTextDatum(middle_center);
  M5.Display.drawString("String 1", BUTTON1_X + BUTTON_WIDTH / 2, BUTTON_Y + BUTTON_HEIGHT / 2);
  
  // Button 2 - String 2
  M5.Display.fillRoundRect(BUTTON2_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_RADIUS, ORANGE_COLOR);
  M5.Display.setTextColor(BLACK_COLOR, ORANGE_COLOR);
  M5.Display.drawString("String 2", BUTTON2_X + BUTTON_WIDTH / 2, BUTTON_Y + BUTTON_HEIGHT / 2);
  
  // Button 3 - String 3
  M5.Display.fillRoundRect(BUTTON3_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_RADIUS, ORANGE_COLOR);
  M5.Display.setTextColor(BLACK_COLOR, ORANGE_COLOR);
  M5.Display.drawString("String 3", BUTTON3_X + BUTTON_WIDTH / 2, BUTTON_Y + BUTTON_HEIGHT / 2);
  
  M5.Display.unloadFont();
}

void loop() {
  M5.update();
  auto touchDetail = M5.Touch.getDetail();

  // Handle RS485 reception
  if (Serial2.available()) {
    char ch = Serial2.read();
    // Ignore carriage return '\r' to prevent extra newlines
    if (ch != '\r') {  
      rs485_str += ch;
    }
    // Check for newline '\n' as line terminator
    if (ch == '\n') {  
      Serial.print("Received: ");
      Serial.print(rs485_str);  // Now only contains '\n' for line breaks
      rs485_str = "";
    }
  }

  if (touchDetail.isPressed()) {
    // Button 1 - Send Test Message 1
    if (touchDetail.x > BUTTON1_X && touchDetail.x < BUTTON1_X + BUTTON_WIDTH && 
        touchDetail.y > BUTTON_Y && touchDetail.y < BUTTON_Y + BUTTON_HEIGHT) {
      if (deb == 0) {
        deb = 1;
        Serial.println("Button 1 pressed");
        Serial2.write("Hello World from TAB5 - Button 1\r\n");
        M5.Speaker.tone(3000, 50);
      }
    }
    
    // Button 2 - Send Test Message 2
    else if (touchDetail.x > BUTTON2_X && touchDetail.x < BUTTON2_X + BUTTON_WIDTH && 
             touchDetail.y > BUTTON_Y && touchDetail.y < BUTTON_Y + BUTTON_HEIGHT) {
      if (deb == 0) {
        deb = 1;
        Serial.println("Button 2 pressed");
        Serial2.write("Hello World from TAB5 - Button 2\r\n");
        M5.Speaker.tone(3000, 50);
      }
    }
    
    // Button 3 - Send Test Message 3
    else if (touchDetail.x > BUTTON3_X && touchDetail.x < BUTTON3_X + BUTTON_WIDTH && 
             touchDetail.y > BUTTON_Y && touchDetail.y < BUTTON_Y + BUTTON_HEIGHT) {
      if (deb == 0) {
        deb = 1;
        Serial.println("Button 3 pressed");
        Serial2.write("Hello World from TAB5 - Button 3\r\n");
        M5.Speaker.tone(3000, 50);
      }
    }
  } else {
    deb = 0;
  }

  delay(1);
}

