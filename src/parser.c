#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int parser_add_flag(ParserConfig* config, char* flag_name, TYPE flag_type, bool required) 
{
    if (config->current_flag < MAX_FLAGS)
    {
        Flag f;
        f.name = flag_name;
        f.value = NULL;
        f.type = flag_type;
        f.required = required;
        f.is_used = false;

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
   
    parser_add_flag(&p, "--help", BOOL, false);
    parser_add_flag(&p, "--version", BOOL, false);

    return p;
}

char* parser_generate_help_message(ParserConfig* config)
{
    return
        "Usage: %s ";
}

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

bool is_flag(ParserConfig* config, int flag_index, char* arg)
{
    return strcmp(config->flags[flag_index].name, arg) == 0;
}


void parser_set_flag_value(ParserConfig* config, int flag_index, char* value) 
{
    if (config->flags[flag_index].type == BOOL)
        config->flags[flag_index].value = "true";
    else
        config->flags[flag_index].value = value; 

    config->flags[flag_index].is_used = true;
}

int parser_validate_flags(ParserConfig* config)
{
    for (int i=0; i<config->current_flag; i++)
        if (config->flags[i].required && !config->flags[i].is_used)
        {
            printf("Error: missing required flag '%s'\n", config->flags[i].name);
            return 1;
        }

    return 0;
}


int parser_parse(ParserConfig* config, int argc, char** argv) 
{
    if (argc < 2)
    {
        printf("Print help message\n"); 
        return 1;
    }
    
    for (int i=0; i<argc; i++)
        for (int current_index=0; current_index<config->current_flag; current_index++) 
            if (is_flag(config, current_index, argv[i]))
                parser_set_flag_value(config, current_index, argv[i+1]);

    return parser_validate_flags(config);
}


void parser_print_flags(ParserConfig config)
{
    for (int i=0; i<config.current_flag; i++)
        printf("%s: %s\n", config.flags[i].name, config.flags[i].value);
}

// finds the flag and returns a pointer to it (helper function)
Flag* get_flag(ParserConfig* config, const char* flag_name)
{
    for (int i=0; i<config->current_flag; i++)
        if (strcmp(config->flags[i].name, flag_name) == 0)
            return &config->flags[i];

    return NULL;
}


bool parser_flag_was_used(ParserConfig* config, const char* flag_name)
{
    Flag* target_flag = get_flag(config, flag_name);
    if (target_flag)
        return target_flag->is_used;
    else
        return false;
}

char* parser_get_flag_value_string(ParserConfig* config, const char* flag_name)
{
    Flag* target_flag = get_flag(config, flag_name);
    if (target_flag)
        return target_flag->value;
    else
        return NULL;
}

int parser_get_flag_value_int(ParserConfig* config, const char* flag_name)
{
    Flag* target_flag = get_flag(config, flag_name);
    if (target_flag)
    {
        if (target_flag->value == NULL) 
            return 0;
        else
            return atoi(target_flag->value);
    }
    else
        return 0;
}

bool parser_get_flag_value_bool(ParserConfig* config, const char* flag_name)
{
    Flag* target_flag = get_flag(config, flag_name);
    if (target_flag)
    {
        if (target_flag->value == NULL) 
            return false;
        else
            return strcmp(target_flag->value, "true") == 0;
    }

    else
        return false;
}
