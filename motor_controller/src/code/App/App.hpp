#pragma once

#include "hw/tb6612/Motor_driver.hpp"
#include "code/Rosserial/ros.h"
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
    //hw::tb6612::Motor_driver _motor_drv;
    //ros::NodeHandle _ros_node;
    //ros::Publisher _ros_motor;
    hw::uart::Serial _serial_drv;

};

}

extern "C" void app_run(void);
