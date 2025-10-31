/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
/*
 * @Hardwares: M5AtomLite + Unit RS485-ISO
 * @Platform Version: Arduino M5Stack Board Manager v3.2.2
 * @Dependent Library:
 * M5Stack@^0.4.6: https://github.com/m5stack/M5Stack
 */
//M5Atom_Isolated_RS485.ino
#include <M5Atom.h>

String str = "";
unsigned long lastPressTime = 0;
bool waitForDoublePress = false;

void setup()
{
    M5.begin(true, false, true);
    // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
    Serial.begin(115200);
    Serial2.begin(115200, SERIAL_8N1, 32, 26);
    Serial.println("RS485 Communication Ready");
}

void loop()
{
    M5.update();
    
    // Handle button press detection
    if (M5.Btn.wasPressed()) {
        unsigned long currentTime = millis();
        
        if (waitForDoublePress && (currentTime - lastPressTime) < 500) {
            // Double press detected
            Serial2.write("Double Press on Button\r\n");
            Serial.println("Sent: Double Press on Button");
            waitForDoublePress = false;
        } else {
            // Single press detected, wait for possible double press
            waitForDoublePress = true;
            lastPressTime = currentTime;
        }
    }
    
    // Check if we should timeout the single press
    if (waitForDoublePress && (millis() - lastPressTime) > 500) {
        // Single press timeout reached
        Serial2.write("Button Press on Button\r\n");
        Serial.println("Sent: Button Press on Button");
        waitForDoublePress = false;
    }

    // Handle incoming RS485 messages
    if (Serial2.available()) {
        char ch = Serial2.read();
        str += ch;
        if (str.endsWith("\r\n")) {
            Serial.print("Received: ");
            Serial.print(str);
            str = "";
        }
    }
}