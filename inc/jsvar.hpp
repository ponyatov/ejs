#pragma once

/// @defgroup var var
/// @ingroup esp
/// @brief `jsvar` -> @ref jvar
/// @{

/// Init/kill vars as a whole.
///
/// If @ref JSVAR_MALLOC is defined, a size can be
/// specified (or 0 uses the old size). Calls @ref jsvReset
void jsvInit(unsigned int size);

/// wipe all JsVars, reset the free list
void jsvReset();

#ifdef RESIZABLE_JSVARS
// Probably Linux - 32 bits allow us to allocate more blocks of variables,
// but is a lot less efficient with memory
typedef uint32_t JsVarRef;
#else
#if JSVAR_FORCE_16_BYTE         // Forces full 16 bits used -> 16 bit JsVar
// This creates less (and faster) code for the Espruino interpreter,
// but isn't as efficient with memory.
#elif JSVAR_CACHE_SIZE <= 8191  // 13 bytes
/// @brief @ref JsVarRef stores References for variables - We treat 0 as null
///
/// NOTE: we store @ref JSVAR_DATA_STRING as actual values
/// so we can do #if on them below
typedef uint16_t JsVarRef;
#else
#endif  // JSVAR_FORCE_16_BYTE

#endif  // RESIZABLE_JSVARS

/// reference of first unused variable (variables are in a linked list)
/// @ref jsvCreateEmptyVarList in @ref jsvSoftInit sets this
extern volatile JsVarRef jsVarFirstEmpty;

/// @}
