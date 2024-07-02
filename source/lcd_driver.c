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
	//PORT_SetPinMux(PORTC, configLCD->kCePin, kPORT_MuxAsGpio); // CE
	PORT_SetPinMux(PORTC, configLCD->kDcPin, kPORT_MuxAsGpio); // D~C

	// init the pins
	GPIO_PinInit(GPIOC, configLCD->rstPin, &gpio_output_config);  // rst pin
	//GPIO_PinInit(GPIOC, configLCD->kCePin, &gpio_output_config);  // CE pin
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
/*
uint8_t printLCD(char character){

	const unsigned char newLine = '\n';

	if(character == newLine){

		configLCD->cursorX = 0;
		configLCD->cursorY = (configLCD->cursorY + 1) % TOTAL_ROWS;
		setCursor(configLCD->cursorX,
				  configLCD->cursorY);

		//si se regresa a la fila 0, significa que nos quedamos sin espacio para escribir
		return configLCD->cursorY == 0;
	}



}
*/

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

/*
uint8_t setCursor(uint8_t x, uint8_t y){
	if(x >= MAX_WIDTH || y >= TOTAL_ROWS){
		return FALSE;
	}

	configLCD->cursorX = x;
	configLCD->cursorY = y;
	GPIO_PinWrite(GPIOC,configLCD->kDcPin,0); // is command
	SPI_SendData( (X_ADDR | x), 1); //rows
	SPI_SendData( (Y_ADDR | y), 1);	//column

	return TRUE;
}
*/
LCD5110_t* LCD5110_make(uint8_t cursorX, uint8_t cursorY){

	static LCD5110_t configLCD;

	configLCD.cursorX = cursorX;
	configLCD.cursorY = cursorY;

	return &configLCD;
}

void clearLCD() {
    // Set the DC pin to command mode
    GPIO_PinWrite(GPIOC, configLCD->kDcPin, FALSE);

    // Iterate through each row and column to clear the screen
    for (uint8_t y = 0; y < TOTAL_ROWS; y++) {
        setCursor(0, y); // Set cursor to the beginning of the row

        // Set the DC pin to data mode
        GPIO_PinWrite(GPIOC, configLCD->kDcPin, 1);

        for (uint8_t x = 0; x < MAX_WIDTH; x++) {
            uint8_t empty = 0x00; // Empty byte
            SPI_SendData(&empty, 1);
        }
    }

    // Reset the cursor position
    setCursor(0, 0);
}
