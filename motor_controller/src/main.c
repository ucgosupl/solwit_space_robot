/*
 * File: main.c
 * Author: GAndaLF
 * Brief: Main file for main_program target.
 */

#include "platform_specific.h"

#include "hw/core_init/core_init.h"
#include "hw/tb6612/tb6612.h"

void main(void)
{
    core_init();

    /* Place your initialisation code here. */
    tb6612_init();
    tb6612_test();

    /* Place your application code here. */

    while (1)
        ;
}
