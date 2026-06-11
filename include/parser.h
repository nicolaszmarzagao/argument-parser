#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

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
    bool required; 
    bool is_used;
} Flag;    

typedef struct {
    const char* program_name;
    const char* description;
    char* version;
    Flag flags[MAX_FLAGS];
    int current_flag;
} ParserConfig;

// Inicialization functions
ParserConfig parser_new(const char* program_name, char* version, const char* description);
int parser_add_flag(ParserConfig* config, char* flag_name, TYPE flag_type, bool needed);
int parser_parse(ParserConfig* config, int argc, char** argv);

// Getter functions
char* parser_get_flag_value_string(ParserConfig* config, const char* flag_name);
int parser_get_flag_value_int(ParserConfig* config, const char* flag_name);
bool parser_get_flag_value_bool(ParserConfig* config, const char* flag_name);

// Other
bool parser_flag_was_used(ParserConfig* config, const char* flag_name);
char* parser_generate_help_message(ParserConfig* config);
void parser_print_flags(ParserConfig config);

#endif
