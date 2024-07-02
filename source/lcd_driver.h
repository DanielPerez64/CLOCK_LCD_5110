/*
    lcd_driver header file
    Author: Daniel Perez
*/
#ifndef LCD_5110_H
#define LCD_5110_H

#include "stdint.h"

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

// variables
//static LCD5110_t* configLCD;

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
#endif //LCD_5110_H
