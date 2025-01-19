#include <Arduino.h>

#ifndef LOG_H
#define LOG_H
extern bool do_log;
#endif

void log(const char *msg);
void logf(const char *format, ...);