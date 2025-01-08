#pragma once

#include "usbd_def.hpp"

/// @defgroup device device
/// @brief `usb_device`
/// @ingroup usb
/// @{

void MX_USB_DEVICE_Init(void);
void MX_USB_DEVICE_DeInit(void);

extern USBD_HandleTypeDef hUsbDeviceFS;

/// @}
