#include "utils.h"

char u_strlen(char* str)
{
    char length = 0;
    char* position = str;
    while (*position)
    {
        length++;
        position++;
    }
    return length;
}

boolean u_strmatch(char* test, char* input)
{
    char lTest = u_strlen(test);
    char lInput = u_strlen(input);

    char stringMatch = 0;
    for (short i = 0; i < lInput - lTest && !stringMatch; i++)
    {
        char charMatch = 1;
        for (short j = 0; j < lTest && input[i + j] != test[j]; j++)
            charMatch = 0;
        if (charMatch)
            stringMatch = 1;
    }

    return stringMatch;
}
