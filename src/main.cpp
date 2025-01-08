#include "main.hpp"
#include "syntax.hpp"
#include "hw.hpp"
#include "os.hpp"
#include "espruino.hpp"

int main(int argc, char *argv[]) {
    {
        hw_init();
        os_init();
        _main();
    }
    arg(0, argv[0]);
    for (int i = 1; i < argc; i++) {
        arg(i, argv[i]);
        assert(yyfile = argv[i]);
        assert(yyin = fopen(yyfile, "r"));
        yyparse();
        fclose(yyin);
        yyfile = nullptr;
    }
    {
        os_fini();
        hw_fini();
    }
}

void arg(int argc, char *argv) {  //
    fprintf(stderr, "arg[%i] = <%s>\n", argc, argv);
}

void yyerror(const char *msg) {
    fprintf(stderr, "\n\n%i: %s [%s]\n\n", yylineno, msg, yytext);
    exit(-1);
}

int _main(void) {
#ifdef STM32F4
    // .isr_vector @ .ld file
    SCB->VTOR = (unsigned int)&_VECTOR_TABLE;
#endif  // STM32F4

    jshInit();
    jswHWInit();

#ifdef USB
    MX_USB_DEVICE_Init();
#endif  // USB

#ifdef BTN1_PININDEX
    bool buttonState = false;
    buttonState = jshPinInput(BTN1_PININDEX) == BTN1_ONSTATE;
#endif  // BTN1_PININDEX

    return 0;
}
