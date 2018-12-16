/*
 * File:    core_init.c
 * Author:  GAndaLF
 * Brief:   Core initialization.
 */

#include "platform_specific.h"
#include "stm32f4xx.h"

#include "core_init.h"

/**
 * @addtogroup hw_core
 *
 * @{
 */


void
core_init(void)
{
	/* Start HSE and wait for it to be ready */
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY))
		;

	/* FLASH configuration*/
	FLASH->ACR = FLASH_ACR_ICEN |   /* instruction cache */
			FLASH_ACR_DCEN |        /* data cache */
			FLASH_ACR_PRFTEN |      /* prefetch enable */
			FLASH_ACR_LATENCY_4WS;  /* 4 wait states */

	/* Set HSE as PLL source, set M, N, P, Q miltipliers and dividers */
	RCC->PLLCFGR = (PLL_Q << 24) | RCC_PLLCFGR_PLLSRC_HSE |
			(((PLL_P >> 1) - 1) << 16) | (PLL_N << 6) | PLL_M;
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY))
		;

	/* PLL as core source clock, prescaler 1 for APB2, prescaler 2 for APB1 */
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2 | RCC_CFGR_SW_PLL;
	while (!(RCC->CFGR & RCC_CFGR_SWS_PLL))
		;

	/* FPU initialization */
	SCB->CPACR |= ((3 << 10*2)|(3 << 11*2));
}

/**
 * @}
 */
