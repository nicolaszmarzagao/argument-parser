#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int parser_add_flag(ParserConfig* config, char* flag_name, TYPE flag_type) 
{
    if (config->current_flag < MAX_FLAGS)
    {
        Flag f;
        f.name = flag_name;
        f.value = NULL;
        f.type = flag_type;

        config->flags[config->current_flag] = f;

        config->current_flag++;
        return 1;
    }
    return 0; // too many flags
}


ParserConfig parser_new(const char* program_name, char* version, const char* description) 
{
    ParserConfig p;
    p.program_name = program_name;
    p.description  = description;
    p.version      = version;
    p.current_flag = 0;
   
    parser_add_flag(&p, "--help", BOOL);
    parser_add_flag(&p, "--version", BOOL);

    return p;
}

char* parser_generate_help_message(ParserConfig* config)
{}

/* EXAMPLE
$ curlpy --help
usage: curlpy [-h] [-p PORT] [-i] [-X REQUEST] [-d DATA] url

A implementation of curl with Python3

positional arguments:
  url                   URL curl will connect to.

options:
  -h, --help            show this help message and exit
  -p, --port PORT       Port that curl will connect to.
  -i, --include-headers
                        Keeps HTTP header in output.
  -X, --request REQUEST
                        HTTP methods to use ie. GET, POST...
  -d, --data DATA       Makes a POST request with a body
*/



void parser_parse_flag(ParserConfig* config, char* flag_name, int flag_index, char* value) 
{
    if (strcmp(config->flags[flag_index].name, "--help") == 0) 
    {
        config->flags[flag_index].value = "true";
        printf("Help msg!\n");
        return;
    }
        
    else if (strcmp(config->flags[flag_index].name, "--version") == 0)
    {
        config->flags[flag_index].value = "true";
        printf("Version %s\n", config->version);
        return;
    }

    config->flags[flag_index].value = value;
}


void parser_parse(ParserConfig* config, int argc, char** argv) 
{
    if (argc < 2)
    {
        printf("Print help message\n"); 
        return;
    }
    
    for (int i=0; i<argc; i++)
    {
        for (int j=0; j<config->current_flag; j++) 
        {
            if (strcmp(config->flags[j].name, argv[i]) == 0) 
            {
                parser_parse_flag(config, config->flags[j].name, j, argv[i+1]);
            }
        }
    }
}


void parser_print_flags(ParserConfig config)
{
    for (int i=0; i<config.current_flag; i++)
        printf("%s: %s\n", config.flags[i].name, config.flags[i].value);
}
