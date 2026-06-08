#ifndef PARSER_H
#define PARSER_H

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
    char* version;
    Flag flags[MAX_FLAGS];
    int current_flag;
} ParserConfig;

int parser_add_flag(ParserConfig* config, char* flag_name, TYPE flag_type);
ParserConfig parser_new(const char* program_name, char* version, const char* description);
char* parser_generate_help_message(ParserConfig* config);
void parser_parse(ParserConfig* config, int argc, char** argv);
void parser_print_flags(ParserConfig config);

#endif
