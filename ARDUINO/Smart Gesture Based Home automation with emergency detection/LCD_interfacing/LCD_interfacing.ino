#include <LiquidCrystal.h>

// Define LCD Pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, D4, D5, D6, D7)

void setup() {
  lcd.begin(16, 2);  // Initialize LCD (16 columns, 2 rows)
  lcd.print("Hello, World!"); // Print message on first row
}

void loop() {
  // No need to add anything here
}
