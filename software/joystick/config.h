// ===================================================================================
// User Configurations
// ===================================================================================

#pragma once

// Joystick pin definitions
#define PIN_JOY_X           PA1       // pin connected to joystick poti x-direction
#define PIN_JOY_Y           PA2       // pin connected to joystick poti y-direction
#define PIN_JOY_SW          PC4       // pin connected to joystick switch

// USB pin definitions
#define USB_PORT            C         // [A,C,D] GPIO Port to use with D+ and D-
#define USB_PIN_DP          1         // [0-4] GPIO Number for USB D+ Pin
#define USB_PIN_DM          2         // [0-4] GPIO Number for USB D- Pin

// USB configuration descriptor
#define USB_MAX_POWER_mA    50        // max power in mA 

// USB device descriptor
#define USB_VENDOR_ID       0x1209    // VID
#define USB_PRODUCT_ID      0xc003    // PID
#define USB_DEVICE_VERSION  0x0100    // v1.0 (BCD-format)
#define USB_LANGUAGE        0x0409    // US English

// USB descriptor strings
#define MANUF_STR           "wagiminator"
#define PROD_STR            "TinyJoyStick"
#define SERIAL_STR          "CH32V003HID"
