#ifndef Arduino_h
#define Arduino_h

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

class HardwareSerial
{
public:
    void begin(long baud);
    void end();
    void write(char* buf, size_t len);
    int available();
    string read();
private:
    char* buffer;
};

extern HardwareSerial Serial;

#endif
