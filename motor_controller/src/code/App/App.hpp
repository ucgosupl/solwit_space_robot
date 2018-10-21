#pragma once

#include "hw/tb6612/Motor_driver.hpp"
#include "hw/uart/Serial.hpp"

namespace app
{

class App
{
public:
    App ();

    void init ();
    void run ();

private:
    hw::tb6612::Motor_driver _motor_drv;
    hw::uart::Serial _serial_drv;
};

}

extern "C" void app_run(void);
