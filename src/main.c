#include <stdio.h>
#include "utils.h"

struct ProgramLine
{
    int line;
    char* code;
};

char split_command(char *command, char *args)
{
    
    boolean in_string = false;
    char position = 0;
    char amount = 1;

    for (short i = 0; i < 32; i++)
    {
        if (command[i] == '"') 
        {
            if (in_string) 
            {
                in_string = false;
            }
            else 
            {
                in_string = true;
            }

            position++;
            continue;
        }

        if (command[i] == ' ' && !in_string)
        {
            args[i - position] = 0x1d;
            amount++;
            continue;
        }

        args[i - position] = command[i];

        if (command[i] == '\0')
            break;
    }

    return amount;
}

void bundle_args(char *args, char *bundled_args)
{
    for (short i = 0; i < 32; i++)
    {
        if (args[i] == 0x1d)
            bundled_args[i] = ' ';
        else
            bundled_args[i] = args[i];
        
        if(args[i] == '\0')
            break;
    }
}

void get_command_name(char *args, char *name)
{
    for (short i = 0; i < 8; i++)
    {
        if (args[i] == 0x1d)
        {
            name[i] = '\0';
            break;
        }

        name[i] = args[i];
    }
}

char decode_command(struct ProgramLine *program, char *command, char *running)
{
    

    char args[32];
    char argc = split_command(command, args);
    char name[8];
    get_command_name(args, name);

    if (u_strmatch("exit", name))
    {
        printf("Shutting down...\n");
        *running = 0;
        return 0xf0;
    }
    else if (u_strmatch("echo", name))
    {
        char bundled_args[32];
        bundle_args(args, bundled_args);
        printf("%s", bundled_args);
        return 0x00;
    }
    else
    {
        char out[32];
        for (short i = 0; i < 32; i++) {
            if (name[i] == '\n')
                break;
            if (name[i] == '\0')
                i = 32;
            out[i] = name[i];
        }
        printf("Unknown command: \"%s\"\n", out);
        return 0x01;
    }
    

    return 0x00;
}

int main()
{
    printf("ArduinoCOS v0.2.0\n");
    struct ProgramLine program[64];

    char running = 1;

    while (running)
    {
        printf("$ ");
        char command[32];
        command[0] = '\n';
        fgets(command, 32, stdin);

        if (command[0] == '\n')
            continue;

        char code = decode_command(program, command, &running);

        if (code == 0xf0) 
            running = 0;
    }

}
