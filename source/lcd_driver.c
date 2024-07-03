/*
   driver de la pantalla SPI
*/

#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "lcd_driver.h"
#include "SPI.h"


static LCD5110_t* configLCD;


// initialize the LCD
uint8_t LCD_begin(){

	//configure the pins to control the LCD

	gpio_pin_config_t gpio_output_config = {
				        kGPIO_DigitalOutput,
				        1,
				    };

	configLCD = LCD5110_make(0,0);

	// USING PTC AS GPIO FOR THE LCD 5110
	configLCD->rstPin = 5;
	configLCD->kCePin = 0;
	configLCD->kDcPin = 0;

	//clocking to portC
	CLOCK_EnableClock(kCLOCK_PortC);

	// set pin mux to port c
	PORT_SetPinMux(PORTC, configLCD->rstPin, kPORT_MuxAsGpio); // RESET
	PORT_SetPinMux(PORTC, configLCD->kDcPin, kPORT_MuxAsGpio); // D~C

	// init the pins
	GPIO_PinInit(GPIOC, configLCD->rstPin, &gpio_output_config);  // rst pin
	GPIO_PinInit(GPIOC, configLCD->kDcPin, &gpio_output_config);  // DC pin
	//end pin config

	// SET the pins
	GPIO_PinWrite(GPIOD,configLCD->kCePin, FALSE);
	GPIO_PinWrite(GPIOC,configLCD->kDcPin, FALSE);
	GPIO_PinWrite(GPIOC,configLCD->rstPin, TRUE);

	// RESET THE LCD
	GPIO_PinWrite(GPIOC,configLCD->rstPin, FALSE);
	GPIO_PinWrite(GPIOC,configLCD->rstPin, TRUE);


	// send the commands
	uint8_t cmdToTransfer[6] = {EXTENDED_CMD,VOP_CONTRAST,TEMP_COF,LCD_BIAS,FUNCT_SET,NORMAL_MODE};
	GPIO_PinWrite(GPIOC,configLCD->kDcPin, FALSE);
    SPI_SendData(cmdToTransfer, 6);

    return 0;
}

// configure the LCD
void setContrast(uint8_t contrast){

	GPIO_PinWrite(GPIOC,configLCD->kDcPin,0); // is command
	uint8_t contrastConfig[3] = {EXTENDED_CMD, (0x80 | contrast), FUNCT_SET};
    SPI_SendData(contrastConfig, 3);
}

// draw in display
uint8_t draw(uint8_t *toDraw, uint32_t size){
	GPIO_PinWrite(GPIOC,configLCD->kDcPin, TRUE); //is data
	SPI_SendData(toDraw, size);
	GPIO_PinWrite(GPIOC,configLCD->kDcPin, FALSE);
	return 0;
}

//set cursor
uint8_t setCursor(uint8_t x, uint8_t y){
    if(x >= MAX_WIDTH || y >= TOTAL_ROWS){
        return FALSE;
    }

    configLCD->cursorX = x;
    configLCD->cursorY = y;
    GPIO_PinWrite(GPIOC, configLCD->kDcPin, 0); // is command

    uint8_t xCommand = X_ADDR | x;
    uint8_t yCommand = Y_ADDR | y;

    SPI_SendData(&xCommand, 1); // rows
    SPI_SendData(&yCommand, 1); // column

    return TRUE;
}

LCD5110_t* LCD5110_make(uint8_t cursorX, uint8_t cursorY){

	static LCD5110_t configLCD;

	configLCD.cursorX = cursorX;
	configLCD.cursorY = cursorY;

	return &configLCD;
}

void clearLCD() {
    GPIO_PinWrite(GPIOC, configLCD->kDcPin, FALSE);
    for (uint8_t y = 0; y < TOTAL_ROWS; y++) {
        setCursor(0, y);
        GPIO_PinWrite(GPIOC, configLCD->kDcPin, 1);
        for (uint8_t x = 0; x < MAX_WIDTH; x++) {
            uint8_t empty = 0x00;
            SPI_SendData(&empty, 1);
        }
    }
    setCursor(0, 0);
}

void print_clock_on_lcd(clock* clock) {
    uint8_t ascii_vector[9];
    clock_to_vector(clock, ascii_vector);

    for (int i = 0; i < 8; i++) {
        if (ascii_vector[i] == ':') {
            draw((uint8_t*)arrayDefault[10], 5);
        } else {
            uint8_t index = ascii_vector[i] - '0';
            draw((uint8_t*)arrayDefault[index], 5);
        }
    }
}
