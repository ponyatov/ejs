#pragma once

/// @defgroup jsw jsw
/// @brief `wrapper`
/// @ingroup esp
/// @{

/// Tasks to run on Hardware Initialisation
/// (called once at boot time, after
/// @ref jshInit, before @ref jsvInit etc)
void jswHWInit();

/// @}
