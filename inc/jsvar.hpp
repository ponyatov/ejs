#pragma once

#include "espruino.hpp"

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

// This creates less (and faster) code for the Espruino interpreter,
// but isn't as efficient with memory.
#if JSVAR_CACHE_SIZE <= 8191  // 13 bytes
/// @brief @ref JsVarRef stores References for variables - We treat 0 as null
///
/// NOTE: we store @ref JSVAR_DATA_STRING as actual values
/// so we can do #if on them below
typedef uint16_t JsVarRef;
#endif  // JSVAR_CACHE_SIZE

/// reference of first unused variable (variables are in a linked list)
/// @ref jsvCreateEmptyVarList in @ref jsvSoftInit sets this
extern volatile JsVarRef jsVarFirstEmpty;

#include "jsutils.hpp"

typedef uint16_t JsVarArrayBufferLength;
#define JSV_ARRAYBUFFER_MAX_LENGTH 0xFFFF
#define JSV_ARRAYBUFFER_LENGTH_BITS :16

typedef enum {
    ARRAYBUFFERVIEW_UNDEFINED = 0,
    ARRAYBUFFERVIEW_MASK_SIZE = 15,
    ARRAYBUFFERVIEW_SIGNED = 16,
    ARRAYBUFFERVIEW_FLOAT = 32,
    /// As in @ref Uint8ClampedArray - clamp to the acceptable bounds
    ARRAYBUFFERVIEW_CLAMPED = 64,
    ARRAYBUFFERVIEW_ARRAYBUFFER = 1 | 128,  ///< basic @ref ArrayBuffer type
    ARRAYBUFFERVIEW_UINT8 = 1,
    ARRAYBUFFERVIEW_INT8 = 1 | ARRAYBUFFERVIEW_SIGNED,
    ARRAYBUFFERVIEW_UINT16 = 2,
    ARRAYBUFFERVIEW_INT16 = 2 | ARRAYBUFFERVIEW_SIGNED,
    ARRAYBUFFERVIEW_UINT24 = 3,
    ARRAYBUFFERVIEW_UINT32 = 4,
    ARRAYBUFFERVIEW_INT32 = 4 | ARRAYBUFFERVIEW_SIGNED,
    ARRAYBUFFERVIEW_FLOAT32 = 4 | ARRAYBUFFERVIEW_FLOAT,
    ARRAYBUFFERVIEW_FLOAT64 = 8 | ARRAYBUFFERVIEW_FLOAT,
} PACKED_FLAGS JsVarDataArrayBufferViewType;

/// Data for @ref ArrayBuffers.
/// Max size here is 6 bytes in most cases (4 byte data + 2x JsVarRef)
typedef struct {
    unsigned short byteOffset;
    JsVarArrayBufferLength length JSV_ARRAYBUFFER_LENGTH_BITS;
    JsVarDataArrayBufferViewType type;
} PACKED_FLAGS JsVarDataArrayBufferView;

/** Union that contains all the different types of data. This should all
 be @ref JSVAR_DATA_STRING_MAX_LEN long.
 */
typedef union {
    char str[JSVAR_DATA_STRING_MAX_LEN];  ///< The contents of this variable if
                                          ///< it is a string
    ///< NOTE: For str above, we INTENTIONALLY OVERFLOW str (and hence data) in
    ///< the case of @ref STRING_EXTS to overwrite 3 references in order to grab
    ///< another 6 bytes worth of string data
    JsVarInt integer;     ///< The contents of this variable if it is an int
    JsVarFloat floating;  ///< The contents of this variable if it is a double
    JsVarDataArrayBufferView
        arraybuffer;               ///< information for array buffer views.
    JsVarDataNative native;        ///< A native function
    JsVarDataNativeStr nativeStr;  ///< A native string (or flash string)
    JsVarDataRef ref;              ///< References
} PACKED_FLAGS JsVarData;

/// These flags are at the top of each @ref JsVar
/// provides information about what it is, as well as how many Locks it has.
/// Everything is packed in as much as possible to allow us to get down to
/// within 2 bytes.
typedef enum {
    /// Variable not used for anything - THIS ENUM MUST BE ZERO
    /// @ref UNDEFINED is now just stored using '0' as the variable Ref
    JSV_UNUSED = 0,
    /// The root of everything - there is only one of these
    JSV_ROOT = JSV_UNUSED + 1,
    JSV_NULL = JSV_ROOT + 1,  ///< it seems null is its own data type

    JSV_ARRAY,  ///< A JavaScript Array Buffer
    ///< Implemented just like a @ref String at the moment
    JSV_ARRAYBUFFER,  ///< An arraybuffer (see @ref varData.arraybuffer)
    JSV_OBJECT,
#ifndef ESPR_NO_GET_SET
    JSV_GET_SET,  ///< Getter/setter (an object with get/set fields)
#endif
    JSV_FUNCTION,
    JSV_NATIVE_FUNCTION,
    JSV_FUNCTION_RETURN,  ///< A simple function that starts with `return`
                          ///< (which is implicit)
    JSV_INTEGER,          ///< integer number (note JSV_NUMERICMASK)
    _JSV_NUMERIC_START =
        JSV_INTEGER,  ///< --------- Start of numeric variable types
    JSV_FLOAT =
        JSV_INTEGER + 1,  ///< floating point double (note JSV_NUMERICMASK)
    JSV_BOOLEAN = JSV_FLOAT + 1,  ///< boolean (note JSV_NUMERICMASK)
#ifndef ESPR_EMBED
    JSV_PIN,  ///< pin (note JSV_NUMERICMASK)
#endif
    JSV_ARRAYBUFFERNAME,  ///< used for indexing into an ArrayBuffer. varData is
                          ///< an INT in this case
    _JSV_NAME_START =
        JSV_ARRAYBUFFERNAME,  ///< ---------- Start of NAMEs (names of
                              ///< variables, object fields/etc)
    JSV_NAME_INT = JSV_ARRAYBUFFERNAME + 1,  ///< integer array/object index
    _JSV_NAME_INT_START = JSV_NAME_INT,
    JSV_NAME_INT_INT =
        JSV_NAME_INT + 1,  ///< integer array/object index WITH integer value
    _JSV_NAME_WITH_VALUE_START =
        JSV_NAME_INT_INT,  ///< ---------- Start of names that have literal
                           ///< values, NOT references, in firstChild
    JSV_NAME_INT_BOOL = JSV_NAME_INT_INT +
                        1,  ///< integer array/object index WITH boolean value
    _JSV_NAME_INT_END = JSV_NAME_INT_BOOL,
    _JSV_NUMERIC_END =
        JSV_NAME_INT_BOOL,  ///< --------- End of numeric variable types
    JSV_NAME_STRING_INT_0 =
        JSV_NAME_INT_BOOL +
        1,  // array/object index as string of length 0 WITH integer value
    _JSV_STRING_START = JSV_NAME_STRING_INT_0,
    JSV_NAME_STRING_INT_MAX =
        JSV_NAME_STRING_INT_0 + JSVAR_DATA_STRING_NAME_LEN,
    _JSV_NAME_WITH_VALUE_END =
        JSV_NAME_STRING_INT_MAX,  ///< ---------- End of names that have literal
                                  ///< values, NOT references, in firstChild
#ifdef ESPR_UNICODE_SUPPORT
    JSV_NAME_UTF8_STRING,  ///< UTF8 name that just points to a normal string
                           ///< with lastChild, but just tag that the string is
                           ///< a unicode one
#endif
    JSV_NAME_STRING_0,  // array/object index as string of length 0
    JSV_NAME_STRING_MAX = JSV_NAME_STRING_0 + JSVAR_DATA_STRING_NAME_LEN,
    _JSV_NAME_END = JSV_NAME_STRING_MAX,  ///< ---------- End of NAMEs (names of
                                          ///< variables, object fields/etc)
    JSV_STRING_0 = JSV_NAME_STRING_MAX + 1,  // simple string value of length 0
    JSV_STRING_MAX = JSV_STRING_0 + JSVAR_DATA_STRING_LEN,
    JSV_FLAT_STRING =
        JSV_STRING_MAX +
        1,  ///< Flat strings store the length (in chars) as an int, and then
            ///< the subsequent JsVars (in memory) store data
    JSV_NATIVE_STRING =
        JSV_FLAT_STRING + 1,  ///< Native strings store an address and length,
                              ///< and reference the underlying data directly
#ifdef ESPR_UNICODE_SUPPORT
    JSV_UTF8_STRING,  ///< UTF8 that just pointss to a normal string with
                      ///< lastChild, but just tag that the string is a unicode
                      ///< one
#endif
#ifdef SPIFLASH_BASE
    JSV_FLASH_STRING,  ///< Like a native String, but not writable and uses
                       ///< jshFlashRead
    _JSV_STRING_END = JSV_FLASH_STRING,
#else
    _JSV_STRING_END = JSV_NATIVE_STRING,
#endif
    JSV_STRING_EXT_0 =
        _JSV_STRING_END +
        1,  ///< extra character data for string (if it didn't fit in first
            ///< JsVar). These use unused pointer fields for extra characters
    JSV_STRING_EXT_MAX = JSV_STRING_EXT_0 + JSVAR_DATA_STRING_MAX_LEN,
    _JSV_VAR_END = JSV_STRING_EXT_MAX,  ///< End of variable types
    // _JSV_VAR_END is:
    //     39 on systems with 8 bit JsVarRefs
    //     43 on systems with 16 bit JsVarRefs
    //     51 on systems with 32 bit JsVarRefs
    //     81 on a 64 bit platform

    JSV_VARTYPEMASK = NEXT_POWER_2(_JSV_VAR_END) - 1,  // probably this is 63

    JSV_CONSTANT =
        JSV_VARTYPEMASK + 1,  ///< to specify if this variable is a constant or
                              ///< not. Only used for NAMEs
    JSV_NATIVE = JSV_CONSTANT
                 << 1,  ///< to specify if this is a function parameter
    JSV_GARBAGE_COLLECT =
        JSV_NATIVE
        << 1,  ///< When garbage collecting, this flag is true IF we should GC!
    JSV_IS_RECURSING = JSV_GARBAGE_COLLECT
                       << 1,  ///< used to stop recursive loops in jsvTrace
    JSV_LOCK_ONE = JSV_IS_RECURSING << 1,
    JSV_LOCK_MASK = JSV_LOCK_MAX * JSV_LOCK_ONE,
    JSV_LOCK_SHIFT = GET_BIT_NUMBER(
        JSV_LOCK_ONE),  ///< The amount of bits we must shift to get the number
                        ///< of locks - forced to be a constant

    JSV_VARIABLEINFOMASK = JSV_VARTYPEMASK | JSV_NATIVE |
                           JSV_CONSTANT,  // if we're copying a variable, this
                                          // is all the stuff we want to copy
} PACKED_FLAGS JsVarFlags;                // aiming to get this in 2 bytes!

typedef struct JsVarStruct {
    /** The actual variable data, as well as references (see below). Put first
     * so word aligned */
    JsVarData varData;

    /** the flags determine the type of the variable - int/double/string/etc. */
    volatile JsVarFlags flags;
} PACKED_FLAGS JsVar;

extern JsVar *jsVars;

extern unsigned int jsVarsSize;

/// @}
