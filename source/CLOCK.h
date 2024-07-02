/*
 * CLOCK.h
 *
 *  Created on: 2 jul. 2024
 *      Author: emms1
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdint.h>

typedef struct {
    uint8_t hora;
    uint8_t minuto;
    uint8_t segundo;
} clock;


void clock_update(clock* clock);
void clock_increment(clock* clock);
void set_clock(clock* clock, uint8_t hora, uint8_t minuto, uint8_t segundo);
void clock_to_vector(clock* reloj, uint8_t* vector);
#endif /* CLOCK_H_ */
