#include <IRremote.h>  // Include the IRremote library

#define IR_PIN 8  // Define the pin connected to the IR receiver

void setup() {
    Serial.begin(9600);  // Start Serial Monitor
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);  // Start the IR receiver
    Serial.println("IR Receiver ready. Press buttons on your remote...");
}

void loop() {
    if (IrReceiver.decode()) {  // If an IR signal is received
        Serial.print("Received IR Code: 0x");
        Serial.println(IrReceiver.decodedIRData.command, HEX);  // Print button HEX code

        IrReceiver.resume();  // Prepare for the next signal
    }
}
