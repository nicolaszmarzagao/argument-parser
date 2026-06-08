#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLAGS 50

typedef enum {
    NONE,
    STR,
    INT,
} TYPE;

typedef struct {
    const char* name;
    char* value;
    TYPE type;
} Flag;    

typedef struct {
    const char* program_name;
    const char* description;
    float version; // maybe this should be a string as well
    Flag flags[MAX_FLAGS];
    int current_flag;
} ParserConfig;

int parser_add_flag(ParserConfig config, const char* flag_name, TYPE flag_type) 
{
    if (config.current_flag < MAX_FLAGS)
    {
        Flag f;
        f.name = flag_name;
        f.value = NULL;
        f.type = flag_type;

        config.flags[config.current_flag] = f;

        config.current_flag++;
        return 1;
    }
    return 0; // too many flags
}


ParserConfig parser_new(const char* program_name, float version, const char* description) 
{
    ParserConfig p;
    p.program_name = program_name;
    p.description  = description;
    p.version      = version;
    p.current_flag = 0;
   
    parser_add_flag(p, "--help", NONE);
    parser_add_flag(p, "--version", NONE);

    return p;
}

int parser_parse(ParserConfig config, int argc, char** argv) 
{
    if (argc < 2)
    {
        printf("Print help message\n"); 
        return 1;
    }
    
    for (int i=0; i<argc; i++)
    {
        for (int j=0; j<config.current_flag; j++) {
            if (strcmp(config.flags[j].name, argv[i]) == 0) printf("FLAG: %s\n", config.flags[j].name);
        }
    }

    return 0;
}


int main(int argc, char** argv) 
{
    ParserConfig parser = parser_new("hello", 0.1, "A simple hello commandline tool");
    parser_add_flag(parser, "--name", STR);
    parser_add_flag(parser, "--count", INT);
    
    int return_code = parser_parse(parser, argc, argv);
    
    return return_code;
}
