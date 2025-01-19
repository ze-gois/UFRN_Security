#include "./input.h"

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'x' },
  { '4', '5', '6', 'o' },
  { '7', '8', '9', '^' },
  { '<', '0', '>', 'v' }
};

uint8_t colPins[COLS] = { 18, 5, 4, 2 }; // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 23, 22, 21, 19}; // Pins connected to R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void detect_key() {
  char key = keypad.getKey();

  if (key != NO_KEY){  
    Serial.println(key);
    switch (key) {
      case 'x' :
        Serial.println("Aaaa");
        break;
      default:
        Serial.println("Xxxxx");
    }
  }
}