%{
    #include "syntax.hpp"
%}

%defines %union { char c; int n; float f; char *s; }

%token <n> INT

%token <s> LOG
%token <c> LP RP LQ RQ LC RC

%%
syntax: | syntax ex

ex : INT    { fprintf(stderr,"int:%i\n",$1); }
ex : LOG    { fprintf(stderr,"cmd:%s\n",$1); }
ex : LP | RP

%%
