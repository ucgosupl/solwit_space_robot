#pragma once

#include <array>

#include "Motor.hpp"

namespace hw
{
namespace tb6612
{

enum class motor_id_t : uint32_t
{
    MOTOR_1,
    MOTOR_2,
    MOTOR_3,
    MOTOR_4,
    MOTOR_CNT
};

class Motor_driver
{
public:
    Motor_driver();

    void init();
    void motor_speed_set(motor_id_t motor_id, motor_speed_t speed);

private:
    static constexpr uint32_t MOTORS_ARRAY_SIZE =
            static_cast<uint32_t>(motor_id_t::MOTOR_CNT);

    std::array<Motor, MOTORS_ARRAY_SIZE> _motors;

    static void gpio_init(void);
    static void timer_init(void);
};

}
}
