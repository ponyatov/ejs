%{
    #include "syntax.hpp"
    char *yyfile = nullptr;
%}

%option noyywrap yylineno

s   [+\-]
n   [0-9]

%%
\/\/[^\n]*      {}                                          // line comment
[ \t\r\n]+      {}                                          // drop spaces
{s}?{n}+        { yylval.n = atoi(yytext); return INT; }    // integer

"console.log"   { return LOG; }

"("             { return LP;  }
")"             { return RP;  }
"["             { return LQ;  }
"]"             { return RQ;  }
"{"             { return LC;  }
"}"             { return RC;  }

.               { yyerror(""); }                            // any undetected char
