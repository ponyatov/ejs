#include "espruino.hpp"

void MX_USB_DEVICE_Init(void) {
    USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS);
    USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC_HID);
    USBD_Start(&hUsbDeviceFS);
}

void MX_USB_DEVICE_DeInit(void) {
    USBD_Stop(&hUsbDeviceFS);
    USBD_DeInit(&hUsbDeviceFS);
}

USBD_StatusTypeDef USBD_Init(USBD_HandleTypeDef *pdev,
                             USBD_DescriptorsTypeDef *pdesc, uint8_t id) {
    return USBD_FAIL;
}

USBD_StatusTypeDef USBD_DeInit(USBD_HandleTypeDef *pdev) { return USBD_FAIL; }

USBD_StatusTypeDef USBD_Start(USBD_HandleTypeDef *pdev) { return USBD_FAIL; }

USBD_StatusTypeDef USBD_Stop(USBD_HandleTypeDef *pdev) { return USBD_FAIL; }

USBD_StatusTypeDef USBD_RegisterClass(USBD_HandleTypeDef *pdev,
                                      USBD_ClassTypeDef *pclass) {
    return USBD_FAIL;
}

USBD_HandleTypeDef hUsbDeviceFS;
USBD_DescriptorsTypeDef FS_Desc;
USBD_ClassTypeDef USBD_CDC_HID;
