#include "espruino.hpp"

void jsvInit(unsigned int size) {
    assert(size == JSVAR_CACHE_SIZE);
    assert(!jsVars);
    assert(jsVars = (JsVar *)malloc(sizeof(JsVar) * jsVarsSize));
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

const size_t jsVarsSize = JSVAR_CACHE_SIZE;
JsVar *jsVars = nullptr;
