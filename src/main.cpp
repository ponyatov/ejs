#include "main.hpp"
#include "syntax.hpp"
#include "hw.hpp"
#include "os.hpp"

int main(int argc, char *argv[]) {  //
    {
        hw_init();
        os_init();
    }
    arg(0, argv[0]);
    for (int i = 1; i < argc; i++) {  //
        arg(i, argv[i]);
        assert(yyfile = argv[i]);
        assert(yyin = fopen(yyfile, "r"));
        yyparse();
        fclose(yyin);
        yyfile = nullptr;
    }
    os_fini();
    hw_fini();
}

void arg(int argc, char *argv) {  //
    fprintf(stderr, "arg[%i] = <%s>\n", argc, argv);
}

void yyerror(const char *msg) {
    fprintf(stderr, "\n\n%i: %s [%s]\n\n", yylineno, msg, yytext);
    exit(-1);
}
