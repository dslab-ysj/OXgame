/*
 * udelay.h
 *
 *  Created on: 2018. 10. 26.
 *      Author: Weonseok Lee
 */

#ifndef UDELAY_H_
#define UDELAY_H_


#include <tinyara/config.h>
#include <sys/types.h>
#include <tinyara/arch.h>

#define CONFIG_BOARD_LOOPSPER100USEC ((CONFIG_BOARD_LOOPSPERMSEC+5)/10)
#define CONFIG_BOARD_LOOPSPER10USEC  ((CONFIG_BOARD_LOOPSPERMSEC+50)/100)
#define CONFIG_BOARD_LOOPSPERUSEC    ((CONFIG_BOARD_LOOPSPERMSEC+500)/1000)

void up_udelay(useconds_t microseconds)
{
	volatile int i;

	while (microseconds > 1000) {
		for (i = 0; i < CONFIG_BOARD_LOOPSPERMSEC; i++) {
		}
		microseconds -= 1000;
	}

	while (microseconds > 100) {
		for (i = 0; i < CONFIG_BOARD_LOOPSPER100USEC; i++) {
		}
		microseconds -= 100;
	}

	while (microseconds > 10) {
		for (i = 0; i < CONFIG_BOARD_LOOPSPER10USEC; i++) {
		}
		microseconds -= 10;
	}

	while (microseconds > 0) {
		for (i = 0; i < CONFIG_BOARD_LOOPSPERUSEC; i++) {
		}
		microseconds--;
	}
}



#endif /* UDELAY_H_ */
