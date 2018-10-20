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

/** External crystal frequency */
#define HSE_FREQ              8000000ULL
/** Core clock frequency */
#define MCU_CLOCK_FREQ        168000000ULL
/** AHB bus frequency */
#define AHB_CLOCK_FREQ        MCU_CLOCK_FREQ
/** APB2 bus frequency */
#define APB2_CLOCK_FREQ       (MCU_CLOCK_FREQ / 2)
/** APB1 bus frequency */
#define APB1_CLOCK_FREQ       (MCU_CLOCK_FREQ / 4)

/**
 * @}
 */

#endif /* _PLATFORM_SPECIFIC_H_ */
