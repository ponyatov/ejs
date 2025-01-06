#pragma once

#include "libc.hpp"

/// @defgroup syntax syntax
/// @{
extern int yylex();                    ///< lexer
extern int yylineno;                   ///< current line number
extern char* yytext;                   ///< lexeme value
extern FILE* yyin;                     ///< current file handler
extern char* yyfile;                   ///< current file name
extern int yyparse();                  ///< parser
extern void yyerror(const char* msg);  ///< syntax error callback
#include "js.parser.hpp"
/// @}
