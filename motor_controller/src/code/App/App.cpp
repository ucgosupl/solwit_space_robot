#include "App.hpp"

namespace app
{

App::App()
{

}

void App::init()
{
    motor_drv.init();

    motor_drv.motor_speed_set(hw::tb6612::motor_id_t::MOTOR_1, 500);
    motor_drv.motor_speed_set(hw::tb6612::motor_id_t::MOTOR_2, 500);
    motor_drv.motor_speed_set(hw::tb6612::motor_id_t::MOTOR_3, 500);
    motor_drv.motor_speed_set(hw::tb6612::motor_id_t::MOTOR_4, 500);
}

}

extern "C" void app_run(void)
{
    app::App app;

    app.init();

    while (1)
        ;
}
