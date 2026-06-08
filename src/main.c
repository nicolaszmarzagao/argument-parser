#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLAGS 50

typedef enum {
    NONE,
    STR,
    INT,
    BOOL,
} TYPE;

typedef struct {
    char* name;
    char* value;
    TYPE type;
} Flag;    

typedef struct {
    const char* program_name;
    const char* description;
    char* version; // maybe this should be a string as well
    Flag flags[MAX_FLAGS];
    int current_flag;
} ParserConfig;

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

int parser_parse(ParserConfig* config, int argc, char** argv) 
{
    if (argc < 2)
    {
        printf("Print help message\n"); 
        return 0;
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

    return 0;
}


void parser_print_flags(ParserConfig config)
{
    for (int i=0; i<config.current_flag; i++)
        printf("%s: %s\n", config.flags[i].name, config.flags[i].value);
}

int main(int argc, char** argv) 
{
    ParserConfig parser = parser_new("hello", "0.0.1", "A simple hello commandline tool");
    parser_add_flag(&parser, "--name", STR);
    parser_add_flag(&parser, "--count", INT);
    
    int return_code = parser_parse(&parser, argc, argv);
    parser_print_flags(parser);
    
    return return_code;
}
