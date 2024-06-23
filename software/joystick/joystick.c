// ===================================================================================
// Project:   USB Stick for CH32V003 - Game Controller (Joystick)
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
// Standard one-button two-axis HID game controller.
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
// - The device should be detected by your operating system as a standard HID game
//   controller.
// - Use the USB Stick as a standard one-button two-axis game controller.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================
#include <config.h>                               // user configurations
#include <system.h>                               // system functions
#include <gpio.h>                                 // GPIO functions
#include <usb_joystick.h>                         // USB HID joystick functions

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
  JOY_init();                                     // init USB HID game controller
  ADC_init();                                     // init ADC
  ADC_slow();                                     // slow ADC sampling

  ADC_input(PIN_JOY_X);                           // set joystick x-poti as ADC input
  JOY_X_middle = ADC_read();                      // read neutral value
  ADC_input(PIN_JOY_Y);                           // set joystick y-poti as ADC input
  JOY_Y_middle = ADC_read();                      // read neutral value

  // Loop
  while(1) {
    // Set joystick button
    PIN_read(PIN_JOY_SW) ? JOY_release(1) : JOY_press(1);

    // Set joystick axis position
    ADC_input(PIN_JOY_X);
    JOY_X_pos = ((int16_t)ADC_read() - JOY_X_middle) >> 2;
    if(JOY_X_pos >  127) JOY_X_pos =  127;
    if(JOY_X_pos < -127) JOY_X_pos = -127;

    ADC_input(PIN_JOY_Y);
    JOY_Y_pos = ((int16_t)ADC_read() - JOY_Y_middle) >> 2;
    if(JOY_Y_pos >  127) JOY_Y_pos =  127;
    if(JOY_Y_pos < -127) JOY_Y_pos = -127;

    JOY_stick(JOY_X_pos, JOY_Y_pos);
  }
}
