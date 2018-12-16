/*
 * File:    platform_specific.h
 * Author:  GAndaLF
 * Brief:   Platform specific definitions.
 */

#ifndef _PLATFORM_SPECIFIC_H_
#define _PLATFORM_SPECIFIC_H_

/* System includes */
#include <stddef.h>
#include <stdbool.h>

/* Platform includes */
#include "stm32f4xx.h"

/**
 * @defgroup utils_platform
 * @{
 */

#define NOBOARD 0
#define F4DISCOVERY 1
#define NUCLEO_F401RE 2

//#define BOARD F4DISCOVERY
#define BOARD NUCLEO_F401RE

#include "bsp/board.h"

/** External crystal frequency */
#define HSE_FREQ              8000000ULL
/** AHB bus frequency */
#define AHB_CLOCK_FREQ        MCU_CLOCK_FREQ
/** APB2 bus frequency */
#define APB2_CLOCK_FREQ       (MCU_CLOCK_FREQ / 2)
/** APB1 bus frequency */
#define APB1_CLOCK_FREQ       (MCU_CLOCK_FREQ / 4)

//todo: clock freq constants should be accessible with some other mechanism

/**
 * @}
 */

#endif /* _PLATFORM_SPECIFIC_H_ */
