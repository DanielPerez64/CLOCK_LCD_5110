/*
 * CLOCK.c
 *
 *  Created on: 2 jul. 2024
 *      Author: emms1
 */

#include "CLOCK.h"
#include <stdint.h>

void clock_increment(clock* clock) {
    clock->segundo++;
    clock_update(clock);
}

void clock_update(clock* clock) {
	if (clock->segundo == 60) {
    	clock->segundo = 0;
    	clock->minuto++;
    }
    if (clock->minuto == 60) {
    	clock->minuto = 0;
    	clock->hora++;
    }
    if (clock->hora == 24) {
    	clock->hora = 0;
    }
}

void clock_to_vector(clock* reloj, uint8_t* vector) {
    // Formatear la hora, minutos y segundos en dos dígitos
    vector[0] = '0' + reloj->hora / 10;
    vector[1] = '0' + reloj->hora % 10;
    vector[2] = ':';
    vector[3] = '0' + reloj->minuto / 10;
    vector[4] = '0' + reloj->minuto % 10;
    vector[5] = ':';
    vector[6] = '0' + reloj->segundo / 10;
    vector[7] = '0' + reloj->segundo % 10;
    vector[8] = '\0'; // Null-terminator para el string
}

void set_clock(clock* clock, uint8_t hora, uint8_t minuto, uint8_t segundo) {
	clock->hora = hora;
	clock->minuto = minuto;
	clock->segundo = segundo;
}
