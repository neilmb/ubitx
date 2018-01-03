#ifndef PROTOFLAG
#include <Wire.h>
//#include <EEPROM.h>

#include <stdint.h>
#include <inttypes.h>
//#include <pgmspace.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#define PROTOFLAG

/**
 * We need to carefully pick assignment of pin for various purposes.
 * There are two sets of completely programmable pins on the Raduino.
 * First, on the top of the board, in line with the LCD connector is an 8-pin connector
 * that is largely meant for analog inputs and front-panel control. It has a regulated 5v output,
 * ground and six pins. Each of these six pins can be individually programmed
 * either as an analog input, a digital input or a digital output.
 * The pins are assigned as follows (left to right, display facing you):
 *      Pin 1 (Violet), A7, SPARE
 *      Pin 2 (Blue),   A6, KEYER (DATA)
 *      Pin 3 (Green), +5v
 *      Pin 4 (Yellow), Gnd
 *      Pin 5 (Orange), A3, PTT
 *      Pin 6 (Red),    A2, F BUTTON
 *      Pin 7 (Brown),  A1, ENC B
 *      Pin 8 (Black),  A0, ENC A
 *Note: A5, A4 are wired to the Si5351 as I2C interface
 *       *
 * Though, this can be assigned anyway, for this application of the Arduino, we will make the following
 * assignment
 * A2 will connect to the PTT line, which is the usually a part of the mic connector
 * A3 is connected to a push button that can momentarily ground this line. This will be used for RIT/Bandswitching, etc.
 * A6 is to implement a keyer, it is reserved and not yet implemented
 * A7 is connected to a center pin of good quality 100K or 10K linear potentiometer with the two other ends connected to
 * ground and +5v lines available on the connector. This implments the tuning mechanism
 */
#define ENC_A (A0)
#define ENC_B (A1)
#define FBUTTON (A2)
#define PTT   (A3)
#define ANALOG_KEYER (A6)
#define ANALOG_SPARE (A7)

/**
 *  The second set of 16 pins on the Raduino's bottom connector are have the three clock outputs and the digital lines to control the rig.
 *  This assignment is as follows :
 *    Pin   1   2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
 *         GND +5V CLK0  GND  GND  CLK1 GND  GND  CLK2  GND  D2   D3   D4   D5   D6   D7
 *  These too are flexible with what you may do with them, for the Raduino, we use them to :
 *  - TX_RX line : Switches between Transmit and Receive after sensing the PTT or the morse keyer
 *  - CW_KEY line : turns on the carrier for CW
 */
#define TX_RX (7)
#define CW_TONE (6)
#define TX_LPF_A (5)
#define TX_LPF_B (4)
#define TX_LPF_C (3)
#define CW_KEY (2)

#define TX_SSB 0
#define TX_CW 1

/**
 * These are the indices where these user changable settinngs are stored  in the EEPROM
 */
#define MASTER_CAL 0
#define LSB_CAL 4
#define USB_CAL 8
#define SIDE_TONE 12
//these are ids of the vfos as well as their offset into the eeprom storage, don't change these 'magic' values
#define VFO_A 16
#define VFO_B 20
#define CW_SIDETONE 24
#define CW_SPEED 28

void checkPTT(void);                                      // from ubitx_20_standard
void setFrequency(unsigned long f);                       //      ubitx_20_standard
void startTx(byte txMode);                                //      ubitx_20_standard
void stopTx();                                            //      ubitx_20_standard
void ritDisable();                                        //      ubitx_20_standard
void ritEnable(unsigned long f);                          //      ubitx_20_standard
void si5351bx_setfreq(uint8_t clknum, uint32_t fout);     //      ubitx_si5351.cpp
void initOscillators(void);                               //      ubitx_si5351.cpp
void si5351_set_calibration(int32_t cal);                 //      ubitx_si5351.cpp
void updateDisplay(void);                                 //      ubitx_ui.cpp
int btnDown(void);                                        //      ubitx_ui.cpp
int enc_read(void);                                       //      ubitx_ui.cpp
void printLine1(char *c);                                 //      ubitx_ui.cpp
void initMeter(void);                                     //      ubitx_ui.cpp
void printLine1(char *c);                                 //      ubitx_ui.cpp
void printLine2(char *c);                                 //      ubitx_ui.cpp
void doMenu(void);                                        //      ubitx_menu.cpp
void factoryCalibration(int btn);                          //      ubitx_menu.cpp
void menuSetupCarrier(int btn);                           //      ubitx_menu.cpp
void factory_alignment(void);                             //      ubitx_factory_alignmment.cpp
void cwKeyer(void);                                       //      ubitx_keyer.cpp
void cwKeydown(void);                                     //      ubitx_keyer.cpp
void cwKeyUp();                                           //      ubitx_keyer.cpp
void checkCAT(void);                                      //      ubitx_cat.cpp
#endif
