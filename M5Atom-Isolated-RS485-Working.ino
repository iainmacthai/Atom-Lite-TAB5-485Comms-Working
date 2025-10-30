#include <M5Atom.h>

String str = "";

void setup() {
    M5.begin();
    Serial.begin(115200);
    Serial.println("RS485 Communication Ready");
    // Use correct UART pins for Atom Lite (adjust if needed)
    Serial2.begin(115200, SERIAL_8N1, 32, 26);  // Keep your working RX/TX pins
}

void loop() {
    if (M5.Btn.wasPressed()) {
        Serial2.write("Hello World\r\n");
    }

    if (Serial2.available()) {
        char ch = Serial2.read();
        // Ignore carriage return '\r' to prevent extra newlines
        if (ch != '\r') {  
            str += ch;
        }
        // Check for newline '\n' as line terminator
        if (ch == '\n') {  
            Serial.print(str);  // Now only contains '\n' for line breaks
            str = "";
        }
    }
    M5.update();
}
