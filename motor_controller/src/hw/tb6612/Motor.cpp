#include "Motor.hpp"

namespace hw
{
namespace tb6612
{

Motor::Motor(GPIO_TypeDef *gpio_dir,
    GPIO_TypeDef *gpio_pwm,
    uint32_t pin_dir1,
    uint32_t pin_dir2,
    uint32_t pin_pwm,
    uint32_t tim_channel_reg)
    : _gpio_dir{gpio_dir}
    , _gpio_pwm{gpio_pwm}
    , _pin_dir1{pin_dir1}
    , _pin_dir2{pin_dir2}
    , _pin_pwm{pin_pwm}
    , _tim_channel_reg(tim_channel_reg)
{
}

void Motor::init()
{
    //assume GPIO is powered

    // PWM pin init
    gpio_mode_config(_gpio_pwm, _pin_pwm, GPIO_MODE_AF);
    gpio_af_config(_gpio_pwm, _pin_pwm, GPIO_AF_TIM2);

    // DIR pin init
    gpio_mode_config(_gpio_dir, _pin_dir1, GPIO_MODE_OUTPUT);
    gpio_mode_config(_gpio_dir, _pin_dir2, GPIO_MODE_OUTPUT);

    // Reset DIR pins
    _gpio_dir->BSRRH = (1 << _pin_dir1)| (1 << _pin_dir2);
}

void Motor::speed_set(motor_speed_t speed)
{
    _gpio_dir->BSRRL = (1 << _pin_dir1);
    _gpio_dir->BSRRH = (1 << _pin_dir2);
    _tim_channel_reg = speed;
}

void Motor::emergency_stop()
{
    _gpio_dir->BSRRH = (1 << _pin_dir1);
    _gpio_dir->BSRRH = (1 << _pin_dir2);
    _tim_channel_reg = 0;
}

}
}

