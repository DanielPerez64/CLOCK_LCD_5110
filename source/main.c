#include "SPI.h"
#include "lcd_driver.h"
#include "fsl_device_registers.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "PIT.h"
#include "CLOCK.h"
#include "NVIC.h"


int main(void)
{
	uint32_t clock_pit = 0;
	clock clock;

    SPI_Init();
    LCD_begin();
    setContrast(0x35);
    clearLCD();

	CLOCK_SetSimSafeDivs();
	clock_pit = CLOCK_GetFreq(kCLOCK_BusClk);
	PIT_init(clock_pit);

	//interrupts
	NVIC_set_basepri_threshold(PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_0);
	NVIC_global_enable_interrupts;

    set_clock(&clock, 15, 28, 36);

    while (1)
    {

    	if (true == PIT_get_irq_status(PIT_Ch0)){
    		clock_increment(&clock);
    		setCursor(25,2);
    		print_clock_on_lcd(&clock);
    		PIT_clear_irq_status(PIT_Ch0);
    	}

    }
}
