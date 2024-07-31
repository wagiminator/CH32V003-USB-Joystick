// ===================================================================================
// Project:   USB Stick for CH32V003 - Mouse Pointer Controller
// Version:   v1.0
// Year:      2024
// Author:    Stefan Wagner
// Github:    https://github.com/wagiminator
// EasyEDA:   https://easyeda.com/wagiminator
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Controls the mouse pointer with the joystick.
//
// References:
// -----------
// - CNLohr ch32v003fun: https://github.com/cnlohr/ch32v003fun
// - CNLohr rv003usb:    https://github.com/cnlohr/rv003usb
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
//
// Compilation Instructions:
// -------------------------
// - Make sure GCC toolchain (gcc-riscv64-unknown-elf, newlib) and Python3 with PyUSB
//   is installed. In addition, Linux requires access rights to WCH-LinkE programmer.
// - Connect the WCH-LinkE programmer to the MCU board.
// - Run 'make flash'.
//
// Operating Instructions:
// -----------------------
// - Connect the board to your PC via USB while the joystick is in its neutral 
//   position (for calibration at start-up).
// - The device should be detected by your operating system as a standard HID mouse.
// - Use the joystick to control the mouse pointer. The joystick button is mapped to 
//   the left mouse button.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================
#include <config.h>                               // user configurations
#include <system.h>                               // system functions
#include <gpio.h>                                 // GPIO functions
#include <usb_mouse.h>                            // USB HID mouse functions

// ===================================================================================
// Main Function
// ===================================================================================
int main(void) {
  // Variables
  uint16_t JOY_X_middle, JOY_Y_middle;            // joystick neutral position values
  int16_t  JOY_X_pos, JOY_Y_pos;                  // current joystick position values

  // Setup
  PIN_input_AN(PIN_JOY_X);                        // set pins
  PIN_input_AN(PIN_JOY_Y);
  PIN_input_PU(PIN_JOY_SW);

  DLY_ms(1);                                      // wait a bit for USB
  MOUSE_init();                                   // init USB HID mouse
  ADC_init();                                     // init ADC
  ADC_slow();                                     // slow ADC sampling

  ADC_input(PIN_JOY_X);                           // set joystick x-poti as ADC input
  JOY_X_middle = ADC_read();                      // read neutral value
  ADC_input(PIN_JOY_Y);                           // set joystick y-poti as ADC input
  JOY_Y_middle = ADC_read();                      // read neutral value

  // Loop
  while(1) {
    // Set joystick button
    PIN_read(PIN_JOY_SW) ? MOUSE_release(MOUSE_BUTTON_LEFT) : MOUSE_press(MOUSE_BUTTON_LEFT);

    // Set joystick axis position
    ADC_input(PIN_JOY_X);
    JOY_X_pos += ADC_read(); JOY_X_pos -= JOY_X_middle;

    ADC_input(PIN_JOY_Y);
    JOY_Y_pos += ADC_read(); JOY_Y_pos -= JOY_Y_middle;

    MOUSE_move(JOY_X_pos >> 6, JOY_Y_pos >> 6);
    JOY_X_pos &= 0x8038; JOY_Y_pos &= 0x8038;
    DLY_ms(10);
  }
}
