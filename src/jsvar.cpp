#include "espruino.hpp"

void jsvInit(unsigned int size) {
#ifdef RESIZABLE_JSVARS
    NOT_USED(size);
#if defined(ESPR_JIT) && defined(LINUX)
#else
#endif  // LINUX
#elif defined(JSVAR_MALLOC)
#if defined(ESPR_JIT) && defined(LINUX)
#else
#endif  // LINUX
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
#endif  // RESIZABLE_JSVARS
}
