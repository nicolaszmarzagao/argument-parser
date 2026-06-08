#include "parser.h"

int main(int argc, char** argv) 
{
    ParserConfig parser = parser_new("hello", "0.0.1", "A simple hello commandline tool");
    parser_add_flag(&parser, "--name", STR);
    parser_add_flag(&parser, "--count", INT);

    parser_parse(&parser, argc, argv);
    parser_print_flags(parser);

    return 0;
}
