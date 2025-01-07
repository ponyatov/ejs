#pragma once

#ifdef X86_64
#include "x86_64.hpp"
#endif

/// @defgroup hw hw
/// @brief supported hardware platforms
/// @{
void hw_init(void);
void hw_fini(void);
/// @}
