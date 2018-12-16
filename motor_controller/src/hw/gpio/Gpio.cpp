#include "Gpio.hpp"

#include "hw/bitband.hpp"

namespace hw
{
namespace gpio
{

class Utils
{
public:
    static constexpr uint32_t GPIO_BASE = GPIOA_BASE;
    static constexpr uint32_t GPIO_OFFSET = GPIOB_BASE - GPIOA_BASE;

    static constexpr uint32_t calculate_address(Port port)
    {
        //todo try to reinterpret_cast<GPIO_TypeDef *>
        return GPIO_BASE + GPIO_OFFSET * static_cast<int>(port);
    }

    static constexpr uint32_t calculate_rcc_ahb1enr_bit(Port port)
    {
        return 0 + static_cast<int>(port);
    }
};

Gpio::Gpio(Port port)
    : _port(port)
    , _gpio(reinterpret_cast<GPIO_TypeDef *>(Utils::calculate_address(_port)))
{};

void Gpio::init()
{
    bitband_periph_set(&RCC->AHB1ENR, Utils::calculate_rcc_ahb1enr_bit(_port));
}

void Gpio::pin_alternative_mode_config(Pin pin, Mode mode)
{
    //todo: change function parameters in gpio_f4 to uint32_t
    using gpio_f4_pin_t = int32_t;

    gpio_f4_pin_t pin_int = static_cast<gpio_f4_pin_t>(pin);
    gpio_mode_config(_gpio, pin_int, GPIO_MODE_AF);
    gpio_af_config(_gpio, pin_int, mode);
}

} //gpio
} //hw
