#include "parser.h"
#include <stdio.h>

int main(int argc, char** argv) 
{
    // Set up Parser Flags
    ParserConfig parser = parser_new("hello", "0.0.1", "A simple hello commandline tool");

    parser_add_flag(&parser, "--name", STR, true);   // required flag
    parser_add_flag(&parser, "--count", INT, false); // optional flag

    int err = parser_parse(&parser, argc, argv);
    if (err != 0) return err;
    
    // Get values from parsed input
    char* name = parser_get_flag_value_string(&parser, "--name");

    // check if optional flag was used
    int count = 1; // default value
    if (parser_flag_was_used(&parser, "--count"))
        count = parser_get_flag_value_int(&parser, "--count");

    // CLI Functionality
    for (int i=0; i<count; i++)
        printf("Hello %s!\n", name);

    return 0;
}
