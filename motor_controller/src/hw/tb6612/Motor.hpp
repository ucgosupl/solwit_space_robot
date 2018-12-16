#pragma once

extern "C"
{
#include "platform_specific.h"
#include "hw/gpio/gpio_f4.h"
}

#include "hw/hw_register.hpp"

namespace hw
{
namespace tb6612
{

using motor_speed_t = int32_t;
constexpr motor_speed_t MOTOR_SPEED_MAX = 1000;

class Motor
{
public:
    Motor(GPIO_TypeDef *gpio_dir,
    GPIO_TypeDef *gpio_pwm,
    uint32_t pin_dir1,
    uint32_t pin_dir2,
    uint32_t pin_pwm,
    uint32_t tim_channel_reg);

    void init();
    void speed_set(motor_speed_t speed);
    void emergency_stop();

private:
    GPIO_TypeDef * const _gpio_dir;
    GPIO_TypeDef * const _gpio_pwm;

    const uint32_t _pin_dir1;
    const uint32_t _pin_dir2;
    const uint32_t _pin_pwm;

    reg::Hw_register<32> _tim_channel_reg;

    void move_forward(motor_speed_t speed);
    void move_backward(motor_speed_t speed);
};

}
}
