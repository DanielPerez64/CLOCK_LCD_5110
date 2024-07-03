/*
    lcd_driver header file
    Author: Daniel Perez
*/
#ifndef LCD_5110_H
#define LCD_5110_H

#include "stdint.h"
#include "clock.h"

// constants
#define MAX_HEIGHT 	    48
#define MAX_WIDTH   	84
#define ROWS_X_CHAR		8
#define COLS_X_CHAR		5
#define TOTAL_ROWS		9	//HEIGHT/COL_X_CHAR
#define TOTAL_COLUMNS	8

// bool defines
#define TRUE 	1
#define FALSE	0

// LCD_5110 : SPI COMMANDS
typedef enum{

    EXTENDED_CMD = 0x21,
    VOP_CONTRAST = 0xB0,
    TEMP_COF     = 0x04,
    LCD_BIAS     = 0x14,
    FUNCT_SET    = 0x20,
    NORMAL_MODE  = 0x0C, //Display control normal mode
	X_ADDR		 = 0x80,
	Y_ADDR		 = 0x40,

    
} LCD_5110_CMD;

typedef struct {

    uint8_t rstPin;
    uint8_t kDcPin;
    uint8_t kCePin;
    uint8_t cursorX;
    uint8_t cursorY;

} LCD5110_t;


static const uint8_t arrayDefault[][5] = {

    {0x3e, 0x51, 0x49, 0x45, 0x3e}  // 0x30 0
    ,
    {0x00, 0x42, 0x7f, 0x40, 0x00}  // 0x31 1
    ,
    {0x42, 0x61, 0x51, 0x49, 0x46}  // 0x32 2
    ,
    {0x21, 0x41, 0x45, 0x4b, 0x31}  // 0x33 3
    ,
    {0x18, 0x14, 0x12, 0x7f, 0x10}  // 0x34 4
    ,
    {0x27, 0x45, 0x45, 0x45, 0x39}  // 0x35 5
    ,
    {0x3c, 0x4a, 0x49, 0x49, 0x30}  // 0x36 6
    ,
    {0x01, 0x71, 0x09, 0x05, 0x03}  // 0x37 7
    ,
    {0x36, 0x49, 0x49, 0x49, 0x36}  // 0x38 8
    ,
    {0x06, 0x49, 0x49, 0x29, 0x1e}  // 0x39 9
    ,
    {0x00, 0x36, 0x36, 0x00, 0x00}  // 0x3a :

};
// initialize the LCD
uint8_t LCD_begin();

// configure the LCD
void setContrast(uint8_t contrast);

// print on LCD
//uint8_t printLCD(char character);
uint8_t draw(uint8_t *toDraw, uint32_t size);

uint8_t setCursor(uint8_t x, uint8_t y);

// create the LCD5110 structure
LCD5110_t* LCD5110_make(uint8_t cursorX, uint8_t cursorY);
void clearLCD();
void print_clock_on_lcd(clock* clock);
#endif //LCD_5110_H
