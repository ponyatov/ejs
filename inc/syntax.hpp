#pragma once

#include "libc.hpp"

/// @defgroup syntax syntax
/// @ingroup core
/// @{
/// @name lexer
/// @{
extern int yylex();   ///< lexer
extern int yylineno;  ///< current line number
extern char* yytext;  ///< lexeme value
extern FILE* yyin;    ///< current file handler
extern char* yyfile;  ///< current file name
/// @}
/// @name parser
/// @{
extern int yyparse();                  ///< parser
extern void yyerror(const char* msg);  ///< syntax error callback
#include "js.parser.hpp"
/// @}
/// @}
