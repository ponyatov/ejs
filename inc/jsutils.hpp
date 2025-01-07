#pragma once

/// 32-bit bit array
#define BITFIELD_DECL(BITFIELD, N) uint32_t BITFIELD[((N) + 31) / 32]
/// Clear all elements
#define BITFIELD_CLEAR(BITFIELD) memset(BITFIELD, 0, sizeof(BITFIELD))
