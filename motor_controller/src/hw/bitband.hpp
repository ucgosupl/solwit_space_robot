/** \file bitband.hpp
 * \brief Header for bit-banding
 * \author Freddie Chopin, http://www.freddiechopin.info/
 * \date 2012-03-18
 */

/******************************************************************************
* chip: ARMv7-M(E) (Cortex-M3 / Cortex-M4)
* compiler: arm-none-eabi-gcc (GNU Tools for ARM Embedded Processors) 4.6.2
* 	20110921 (release) [ARM/embedded-4_6-branch revision 182083]
******************************************************************************/

#pragma once

/*
+=============================================================================+
| global definitions
+=============================================================================+
*/

#define BITBAND_SRAM_REF   					0x20000000
#define BITBAND_SRAM_BASE  					0x22000000

#define BITBAND_PERIPH_REF   				0x40000000
#define BITBAND_PERIPH_BASE  				0x42000000

/*
+=============================================================================+
| strange variables
+=============================================================================+
*/

//dont need bitband_t, have auto

/*
+=============================================================================+
| macros
+=============================================================================+
*/

template <typename PtrType>
constexpr PtrType * get_bitband_sram_addr(PtrType *address, uint32_t bit)
{
    uint32_t addr_val = reinterpret_cast<uint32_t>(address);

    return reinterpret_cast<PtrType *>(BITBAND_SRAM_BASE + (addr_val- BITBAND_SRAM_REF) * 32 + bit * 4);
}

template <typename PtrType>
constexpr PtrType * get_bitband_periph_addr(PtrType *address, uint32_t bit)
{
    uint32_t addr_val = reinterpret_cast<uint32_t>(address);

    return reinterpret_cast<PtrType *>(BITBAND_PERIPH_BASE + (addr_val- BITBAND_PERIPH_REF) * 32 + bit * 4);

}

/******************************************************************************
* END OF FILE
******************************************************************************/
