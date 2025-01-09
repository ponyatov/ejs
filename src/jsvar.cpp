#include "espruino.hpp"

void jsvInit(unsigned int size) {
#ifdef RESIZABLE_JSVARS
#elif defined(JSVAR_MALLOC)
#else
    assert(size == JSVAR_CACHE_SIZE);
#endif  // RESIZABLE_JSVARS
    jsvReset();
}

volatile JsVarRef jsVarFirstEmpty = 0;

void jsvReset() {
    // @ref jsvCreateEmptyVarList in @ref jsvSoftInit sets this
    jsVarFirstEmpty = 0;

#ifdef RESIZABLE_JSVARS
#else
    memset(jsVars, 0, sizeof(JsVar) * jsVarsSize);
#endif  // RESIZABLE_JSVARS
}
