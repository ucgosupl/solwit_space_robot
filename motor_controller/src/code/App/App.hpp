#pragma once

#include "hw/tb6612/Motor_driver.hpp"
#include "code/Rosserial/ros.h"

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
    ros::NodeHandle _ros_node;
    ros::Publisher _ros_motor;
};

}

extern "C" void app_run(void);
