#pragma once

/** PLL divider for USB - 42 MHz. */
#define PLL_Q   4
/** PLL divider before VCO - 2 MHz */
#define PLL_M   4
/** PLL multiplier - 332 MHz */
#define PLL_N   168
/** PLL divider after VCO - 168 MHz */
#define PLL_P   2

/** Core clock frequency */
#define MCU_CLOCK_FREQ        168000000ULL
