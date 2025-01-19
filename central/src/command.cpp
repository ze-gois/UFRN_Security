#include "./command.h"
#include <Arduino.h>
#include <vector>

static std::vector<Command>commands = {};

void new_once_command(const char * descriptor, const char * pattern, void (*once_function)(void)) {
  Command command;
  command.descriptor = descriptor;
  command.pattern = pattern;
  command.once_function = once_function;
  command.loop_function = nullptr;
  command.interval = 0;
  command.latter_call = 0;
  
  commands.push_back(command);  // No need for dynamic allocation here.
}

void new_command(const char * descriptor, const char * pattern, void (*once_function)(void), void (*loop_function)(void), unsigned long interval) {
  Command command;
  command.descriptor = descriptor;
  command.pattern = pattern;
  command.once_function = once_function;
  command.loop_function = loop_function;
  command.interval = interval;
  command.latter_call = 0;
  
  commands.push_back(command);  // No dynamic allocation needed.
}

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

void obliviate() {
  while (sequence->former) {
    InputMemory* fared = sequence->former;
    sequence->former = sequence->former->descendant;
    delete fared;  // Ensure memory is freed.
  }
  sequence->latter = nullptr;
}

bool obey(Command cmd) {
  int pattern_len = strlen(cmd.pattern);
  InputMemory* current = sequence->latter;

  for (int i = pattern_len - 1; i >= 0 && current != nullptr; i--, current = current->ancestral) {
    if (current->c != cmd.pattern[i]) {
      return false;
    }
  }

  if (cmd.once_function) {
    Serial.print(">>> ");
    Serial.println(cmd.descriptor);
    cmd.once_function();
  } else {
    Serial.println("Command function is null.");
    return false;
  }

  return true;
}

void patience() {
  if ((millis() - last_input_time) > MAX_IDLE_INPUT_TIME && sequence->former) {
    Serial.println("Input timeout, clearing buffer.");
    obliviate();
  }
}

void reflect() {
  for (auto command : commands) {
    if (obey(command)) {
      obliviate();
      return;
    }
  }
}

void review() {
  for (auto command: commands) {
    if (command.loop_function != nullptr) {
      unsigned long current_time = millis();
      if (current_time - command.latter_call > command.interval) {
        command.loop_function();
        command.latter_call = current_time;
      }
    }
  }
}

// #include "./command.h"
// #include <vector>
// #include <Arduino.h>


// void new_once_command(const char * descriptor, const char * pattern, void (*once_function)(void)){
//   Command command;
  
//   command.descriptor = descriptor;
//   command.pattern = pattern;
//   command.once_function = once_function;
//   command.loop_function = nullptr;
//   command.interval = 0;
//   command.latter_call = 0;

//   commands.push_back(command);
// }

// void new_command(const char * descriptor, const char * pattern, void (*once_function)(void),void (*loop_function)(void),unsigned long interval){
//   Command command;
  
//   command.descriptor = descriptor;
//   command.pattern = pattern;
//   command.once_function = once_function;
//   command.loop_function = loop_function;
//   command.interval = interval;
//   command.latter_call = 0;

//   commands.push_back(command);
// }

// void assimilate(char key) {
//   InputMemory* newcommer = new InputMemory{key, sequence->latter, nullptr};
  
//   if (sequence->former == nullptr) {
//       sequence->former = newcommer;
//   } else {
//     if (sequence->former->descendant == nullptr){
//       sequence->former->descendant = newcommer;
//     } else {
//       sequence->latter->descendant = newcommer; 
//     }
//   } 
  
//   sequence->latter = newcommer;
//   last_input_time = millis();
//   return;
// }

// void obliviate() {
//     while (sequence->former) {
//         InputMemory* fared = sequence->former;
//         sequence->former = sequence->former->descendant;
//         delete fared;
//     }
//     sequence->latter = nullptr;
// }

// bool obey(Command cmd) {
//   int pattern_len = strlen(cmd.pattern);
//   InputMemory* current = sequence->latter;

//   for (int i = pattern_len - 1; i >= 0 && current; i--, current = current->ancestral) {
//     if (current->c != cmd.pattern[i]) {
//       return false;
//     }
//   }

//   if (cmd.once_function) {
//     Serial.println(cmd.descriptor);
//     cmd.once_function();
//   } else {
//     Serial.println("Command function is null.");
//     return false;
//   }

//   return true;
// }

// void patience() {
//   if ((millis() - last_input_time) > MAX_IDLE_INPUT_TIME && sequence->former) {
//     Serial.println("Input timeout, clearing buffer.");
//     obliviate();
//   }
// }

// void reflect() {
//   for (auto command : commands) {
//     if (obey(command)) {
//       obliviate();
//       return;
//     }
//   }
// }

// void review() {
//   for (auto command: commands) {
//     if (command.loop_function != nullptr) {
//       unsigned long current_time = millis();
//       if (current_time - command.latter_call > command.interval){
//         command.loop_function();
//         command.latter_call = current_time;
//       }
//     }
//   }
// }

// bool is_on = false;
// int PIN_LED_POWER = 27;
// void toggle_on(void) {
//   is_on = !is_on;
//   if (is_on){
//     Serial.println("Device is ON");
//   } else{
//     Serial.println("Device is OFF");
//   }
//   digitalWrite(PIN_LED_POWER, is_on ? HIGH : LOW);
// }

// int PIN_LED_SECRET = 32;
// int secret_onset_time;
// bool is_secret;

// void secret(void) {
//   if (is_on){
//     Serial.println("Secret was given.");
//     secret_onset_time = millis();
//     is_secret = true; 
//   }
// }

// void secret_loop(void) {
//   if (is_secret){
//     digitalWrite(PIN_LED_SECRET, HIGH);
  
//     if (millis()-secret_onset_time > 5000){
//       digitalWrite(PIN_LED_SECRET, LOW);
//       is_secret = false;
//     }
//   }
// }

// int pow(int b, int e) {
//   if (e == 0) return 1;
//   return b*pow(b,e-1);
// }

// int volume = 0;
// int volume_resolution = 10;
// int volume_max = pow(2,volume_resolution);
// int volume_step = volume_max/5;

// int PIN_LED_VOLUME = 25;
// void increase_volume(void) {
//   if (is_on){
//     if (volume <= (volume_max-volume_step)) {
//       volume += volume_step;
//     } else {
//       volume = volume_max;
//     }
//     //analogWrite(PIN_LED_VOLUME,volume);
//     ledcWrite(PIN_LED_VOLUME,volume);
//     Serial.print("Volume:");
//     Serial.println(volume);
//   }
// }

// void decrease_volume(void) {
//   if (is_on){
//     if (volume >= volume_step) {
//       volume -= volume_step;
//     } else if (volume < volume_step){
//       volume = 0;
//     }
//     //analogWrite(PIN_LED_VOLUME,volume);
//     ledcWrite(PIN_LED_VOLUME,volume);
//     Serial.print("Volume:");
//     Serial.println(volume);
//   }
// }

// void loop_off() {
//   if (!is_on) {
//     is_secret = false;
//     volume = 0;
//     digitalWrite(PIN_LED_POWER, LOW);
//     ledcWrite(PIN_LED_VOLUME,volume);
//     digitalWrite(PIN_LED_SECRET, LOW);
//   }
// }









// int n_commands = 5;

// int IRReciverPin = 15;

// void setup() {
//   Serial.begin(9600);
//   IrReceiver.begin(IRReciverPin);
//   pinMode(PIN_LED_POWER, OUTPUT);
//   //pinMode(PIN_LED_VOLUME, OUTPUT);
//   pinMode(PIN_LED_SECRET, OUTPUT);
//   ledcAttach(PIN_LED_VOLUME, 3,10);
// }

// void loop() {

//   if (IrReceiver.decode()) {
//       int oitive = IrReceiver.decodedIRData.command;

//       IrReceiver.resume();

//       recite();
      
//       assimilate(oitive);

//       reflect();

//       recite();
//   }

//   review();

//   patience();

// }