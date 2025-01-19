#include <Arduino.h>
#include <vector>

typedef struct {
  const char * descriptor;
  const char * pattern;
  void (*once_function)(void);
  void (*loop_function)(void);
  unsigned long interval;
  unsigned long latter_call;
} Command;

struct InputMemory {
  char c;
  InputMemory *ancestral;
  InputMemory *descendant;
};

struct InputSequence {
  InputMemory *former;
  InputMemory *latter;
};

static InputSequence *sequence = new InputSequence{nullptr, nullptr};
static unsigned long last_input_time;
static const unsigned long MAX_IDLE_INPUT_TIME = 3000;

#ifndef COMMAND_H
#define COMMAND_H
extern void new_once_command(const char * descriptor, const char * pattern, void (*once_function)(void));
extern void new_command(const char * descriptor, const char * pattern, void (*once_function)(void),void (*loop_function)(void),unsigned long interval);
extern void assimilate(char key);
extern void obliviate();
extern bool obey(Command cmd);
extern void patience();
extern void reflect();
extern void review();
#endif