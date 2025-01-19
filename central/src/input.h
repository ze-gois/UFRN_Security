#include <Keypad.h>
#ifndef INPUT_H
#define INPUT_H
const uint8_t ROWS = 4;
const uint8_t COLS = 4;

extern char keys[ROWS][COLS];
extern uint8_t colPins[COLS];
extern uint8_t rowPins[ROWS];

void detect_key();
#endif