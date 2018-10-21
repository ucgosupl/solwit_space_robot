/*
 * File: main.c
 * Author: GAndaLF
 * Brief: Main file for main_program target.
 */

#include "platform_specific.h"

#include "hw/core_init/core_init.h"

extern void app_run(void);

int main(void)
{
    /* Place your initialisation code here. */
    core_init();

    /* Place your application code here. */
    app_run();

    while (1)
        ;

    return 0;
}
