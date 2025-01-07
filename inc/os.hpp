#pragma once

#ifdef LINUX
#include "linux.hpp"
#endif

/// @defgroup os os
/// @brief supported OSes
/// @{
void os_init(void);
void os_fini(void);
/// @}
