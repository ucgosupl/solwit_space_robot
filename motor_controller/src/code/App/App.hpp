#pragma once

#include "hw/tb6612/Motor_driver.hpp"

namespace app
{

class App
{
public:
    App ();

    void init ();

private:
    hw::tb6612::Motor_driver motor_drv;
};

}

extern "C" void app_run(void);
