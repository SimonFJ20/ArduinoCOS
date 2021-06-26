#include <iostream>
#include "arduino.h"

void HardwareSerial::begin(long baud)
{
    std::cout << "\n=== Serial begin ===\n\n";
}

void HardwareSerial::end()
{
    std::cout << "\n\n=== Serial end ===\n\n";
}

void HardwareSerial::write(char* buf, size_t len)
{
    std::cout << buf; 
}

int HardwareSerial::available()
{
    return buffer.length();
}

string HardwareSerial::read()
{
    string input;
    std::cin >> input;
    return input;
}

HardwareSerial Serial;

