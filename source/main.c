#include "SPI.h"
#include "lcd_driver.h"
#include "fsl_device_registers.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "PIT.h"
#include "CLOCK.h"

//uint8_t masterTxData[SPI_TRANSFER_SIZE] = {0U};
volatile uint32_t g_systickCounter = 20U;


//claando este vetor
uint8_t masterTxData[SPI_TRANSFER_SIZE] = {0x01, 0x03, 0x05, 0x07, 0x09, 0x0B, 0x0D, 0x0F,
                                         0x11, 0x13, 0x15, 0x17, 0x19, 0x1B, 0x1D, 0x1F,
                                         0x21, 0x23, 0x25, 0x27, 0x29, 0x2B, 0x2D, 0x2F,
                                         0x31, 0x33, 0x35, 0x37, 0x39, 0x3B, 0x3D, 0x3F,
                                         0x41, 0x43, 0x45, 0x47, 0x49, 0x4B, 0x4D, 0x4F,
                                         0x51, 0x53, 0x55, 0x57, 0x59, 0x5B, 0x5D, 0x5F,
                                         0x61, 0x63, 0x65, 0x67, 0x69, 0x6B, 0x6D, 0x6F,
                                         0x71, 0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D, 0x7F};


void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

int main(void)
{
    SPI_Init();
    LCD_begin();
    setContrast(0x35);

    clearLCD();
   //uint32_t i;
   /*
    for(uint8_t i = 0; i < 504 ; i++){
    	draw(0x00,1);
    }
*/
   // setCursor(0,0);
   // uint8_t drawArray[5] = {0x7f, 0x08, 0x08, 0x08, 0x7f};
    uint8_t drawH[5] = {0x7f, 0x08, 0x08, 0x08, 0x7f}; // 'H'
    uint8_t drawO[5] = {0x3e, 0x41, 0x41, 0x41, 0x3e}; // 'O'
    uint8_t drawL[5] = {0x7f, 0x40, 0x40, 0x40, 0x40}; // 'L'
    uint8_t drawA[5] = {0x7e, 0x11, 0x11, 0x11, 0x7e}; // 'A'
    setCursor(32,2);
   // draw(drawArray,5);
    /*
    draw(drawH,5);
    draw(drawO,5);
    draw(drawL,5);
    draw(drawA,5);
*/

    clock miReloj = {12, 34, 56};
    uint8_t vector[9]; // 8 caracteres + null-terminator
    clock_to_vector(&miReloj, vector);

    draw(vector,9);

    while (1)
    {
    	/*
        clock miReloj = {12, 34, 56};
        char vector[9]; // 8 caracteres + null-terminator

        clock_to_vector(&miReloj, vector);
        printf("Vector: %s\n", vector); // Imprime el vector formateado
        */

    	//draw(drawArray,5);
    	//draw(drawArray,5);
    	// draw(masterTxData,SPI_TRANSFER_SIZE);
    //	SPI_SendData(masterTxData,SPI_TRANSFER_SIZE);
/*
        if (SysTick_Config(SystemCoreClock / 1000U))
        {
            while (1)
            {
            }
        }

        g_systickCounter = 20U;
        while (g_systickCounter != 0U)
        {
        }

*/

    }
}
