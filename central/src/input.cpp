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

void assimilate(char key) {
  InputMemory* newcommer = new InputMemory{key, sequence->latter, nullptr};
  
  if (sequence->former == nullptr) {
    sequence->former = newcommer;
  } else {
    if (sequence->former->descendant == nullptr) {
      sequence->former->descendant = newcommer;
    } else {
      sequence->latter->descendant = newcommer;
    }
  } 
  
  sequence->latter = newcommer;
  last_input_time = millis();
}

bool parecer(const char* wit) {
  int wit_len = strlen(wit);
  InputMemory* current = sequence->latter;

  for (int i = wit_len - 1; i >= 0 && current != nullptr; i--, current = current->ancestral) {
    if (current->c != wit[i]) {
      return false;
    }
  }
  return true;
}

void obliviate() {
  while (sequence->former) {
    InputMemory* fared = sequence->former;
    sequence->former = sequence->former->descendant;
    delete fared;  // Ensure memory is freed.
  }
  sequence->latter = nullptr;
}

void patience() {
  if ((millis() - last_input_time) > MAX_IDLE_INPUT_TIME && sequence->former) {
    Serial.println("Input timeout, clearing buffer.");
    obliviate();
  }
}


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