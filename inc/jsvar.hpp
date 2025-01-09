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

#endif  // RESIZABLE_JSVARS

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
