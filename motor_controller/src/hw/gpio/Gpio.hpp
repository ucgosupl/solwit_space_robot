#pragma once

extern "C"
{
#include "platform_specific.h"
#include "hw/gpio/gpio_f4.h"
}

namespace hw
{
namespace gpio
{

enum class Port
{
    A,
    B,
    C,
    D,
    E,
};

enum class Pin
{
   P00,
   P01,
   P02,
   P03,
   P04,
   P05,
   P06,
   P07,
   P08,
   P09,
   P10,
   P11,
   P12,
   P13,
   P14,
   P15,
};

//for now using mode defines from gpio_f4.h, later can update to enum class or something else.
using Mode = uint32_t;

class Gpio
{
public:
    Gpio(Port port);

    void init();
    void pin_alternative_mode_config(Pin pin, Mode mode);

private:
    Port _port;
    GPIO_TypeDef * const _gpio;
};

} //gpio
} //hw
