/*
 * PIT.h
 *
 *  Created on: 7 may 2024
 *      Author: jlpe
 */

#ifndef PIT_H_
#define PIT_H_

#include <stdint.h>

typedef enum
{
	PIT_Ch0,
	PIT_Ch1,
	PIT_Ch2,
	PIT_Ch3

} pit_channel_t;


void PIT_init(uint32_t clock_pit);

void PIT_clear_irq_status(pit_channel_t pit_chn);

uint8_t PIT_get_irq_status(pit_channel_t pit_chn);


#endif /* PIT_H_ */
