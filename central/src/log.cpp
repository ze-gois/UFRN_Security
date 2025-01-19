#include "./log.h"

bool do_log = true;

void log(const char *msg) {
    if (!do_log) return;
    Serial.println(msg);
}

void logf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int size = std::vsnprintf(nullptr, 0, format, args) + 1; 
    va_end(args);
    
    std::string result(size, '\0'); 
    
    va_start(args, format);
    std::vsnprintf(&result[0], size, format, args);
    va_end(args);

    result.pop_back();
    log(result.c_str());
}