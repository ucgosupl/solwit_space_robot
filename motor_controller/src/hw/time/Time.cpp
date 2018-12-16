#include "Time.hpp"

extern "C"
{
#include "platform_specific.h"
#include "hw/gpio/gpio_f4.h"
}

namespace hw
{
namespace time
{

class Utilities
{
public:
    static void init()
    {
        SysTick_Config(AHB_CLOCK_FREQ / 1000);
        NVIC_EnableIRQ(SysTick_IRQn);
    }

    static void irq_handler()
    {
        ms++;
    }

    static time_t ms_get()
    {
        return ms;
    }

private:
    static volatile time_t ms;
};

volatile time_t Utilities::ms = 0;

void time_init()
{
    Utilities::init();
}

time_t ms_get()
{
    return Utilities::ms_get();
}

void delay(time_t ms)
{
    auto start_time = hw::time::ms_get();
    while (ms > hw::time::ms_get() - start_time)
        ;
}

} //time
} //hw

extern "C" void SysTick_Handler(void)
{
    hw::time::Utilities::irq_handler();
}
