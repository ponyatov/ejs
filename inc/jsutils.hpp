#pragma once

/// 32-bit bit array
#define BITFIELD_DECL(BITFIELD, N) uint32_t BITFIELD[((N) + 31) / 32]
/// Clear all elements
#define BITFIELD_CLEAR(BITFIELD) memset(BITFIELD, 0, sizeof(BITFIELD))

/// Max length for a @ref JSV_STRINGEXT, JsVar.varData.ref.lastChild
/// (see comments under @ref JsVar decl in jsvar.h)
#define JSVAR_DATA_STRING_MAX_LEN                                           \
    (JSVAR_DATA_STRING_NAME_LEN +                                           \
     ((JSVARREF_BITS * 3 + JSVARREFCOUNT_PACK_BITS + JSVARREFCOUNT_BITS) >> \
      3))

/// Used when we have enums we want to squash down
#define PACKED_FLAGS __attribute__((__packed__))
