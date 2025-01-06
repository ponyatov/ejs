#pragma once

#ifdef LINUX
#include "linux.hpp"
#endif

/// @defgroup os os
/// @{
void os_init(void);
void os_fini(void);
/// @}
