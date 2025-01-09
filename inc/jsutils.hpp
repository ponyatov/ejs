#pragma once

/// @defgroup utils utils
/// @ingroup esp
/// @{

/// 32-bit bit array
#define BITFIELD_DECL(BITFIELD, N) uint32_t BITFIELD[((N) + 31) / 32]
/// Clear all elements
#define BITFIELD_CLEAR(BITFIELD) memset(BITFIELD, 0, sizeof(BITFIELD))

/// Max length of JSV_NAME_ strings
#define JSVAR_DATA_STRING_NAME_LEN 4
/// these should be the same, but if we use sizeof in the `#defines`
/// below they won't be constant
#define JSVAR_DATA_STRING_NAME_LEN_ sizeof(size_t)

#if JSVAR_CACHE_SIZE <= 8191  // 13 bytes
#define JSVARREF_BITS 13
#define JSVARREFCOUNT_BITS (56 - 13 * 4)
#endif  // JSVAR_CACHE_SIZE

#ifndef JSVARREFCOUNT_PACK_BITS
#define JSVARREFCOUNT_PACK_BITS 0
#endif

/// Max length for a JSV_STRING, JsVar.varData.ref.refs (see comments under
/// JsVar decl in jsvar.h)
#define JSVAR_DATA_STRING_LEN     \
    (JSVAR_DATA_STRING_NAME_LEN + \
     ((JSVARREF_BITS * 3 + JSVARREFCOUNT_PACK_BITS) >> 3))

/// Max length for a @ref JSV_STRINGEXT, JsVar.varData.ref.lastChild
/// (see comments under @ref JsVar decl in jsvar.h)
#define JSVAR_DATA_STRING_MAX_LEN                                           \
    (JSVAR_DATA_STRING_NAME_LEN +                                           \
     ((JSVARREF_BITS * 3 + JSVARREFCOUNT_PACK_BITS + JSVARREFCOUNT_BITS) >> \
      3))

/// Used when we have enums we want to squash down
#define PACKED_FLAGS __attribute__((__packed__))

/// preprocessor power of 2 - suitable up to 16 bits
#define NEXT_POWER_2(X)                                                       \
    (((X) | (X) >> 1 | (X) >> 2 | (X) >> 3 | (X) >> 4 | (X) >> 5 | (X) >> 6 | \
      (X) >> 7 | (X) >> 8 | (X) >> 9 | (X) >> 10 | (X) >> 11 | (X) >> 12 |    \
      (X) >> 13 | (X) >> 14 | (X) >> 15) +                                    \
     1)

/// Maximum amount of locks we ever expect to have on a variable
/// (this could limit recursion) must be `2^n-1`
#define JSV_LOCK_MAX 15

/// Proprocessor get bit number
#define GET_BIT_NUMBER(X)  \
    (((X) == 1)       ? 0  \
     : ((X) == 2)     ? 1  \
     : ((X) == 4)     ? 2  \
     : ((X) == 8)     ? 3  \
     : ((X) == 16)    ? 4  \
     : ((X) == 32)    ? 5  \
     : ((X) == 64)    ? 6  \
     : ((X) == 128)   ? 7  \
     : ((X) == 256)   ? 8  \
     : ((X) == 512)   ? 9  \
     : ((X) == 1024)  ? 10 \
     : ((X) == 2048)  ? 11 \
     : ((X) == 4096)  ? 12 \
     : ((X) == 8192)  ? 13 \
     : ((X) == 16384) ? 14 \
     : ((X) == 32768) ? 15 \
                      : 10000 /*error*/)

/// @}
