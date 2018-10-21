#include "hw/uart/Serial.hpp"
#include "hw/time/Time.hpp"

#include "App.hpp"

namespace app
{

//todo how to initialize publisher message?
App::App()
    : _ros_motor{"motor", nullptr}
{

}

void App::init()
{
    __enable_irq();

    hw::time::time_init();

    _motor_drv.init();

    _ros_node.initNode();
    _ros_node.advertise(_ros_motor);
}

void App::run()
{
//    const char test_string[] = "Testowy string 123456\n";
//
//    _serial_drv.send((uint8_t *)test_string, sizeof(test_string) - 1);

    //todo: motors not active only for tests
    while (1)
    {
        _ros_node.spinOnce();

        //todo: optional delay
    }

    while (1)
    {
        _motor_drv.move_forward(500);

        hw::time::delay(3000);

        _motor_drv.move_backward(500);

        hw::time::delay(3000);

        _motor_drv.move_left(500);

        hw::time::delay(3000);

        _motor_drv.move_right(500);

        hw::time::delay(3000);
    }
}

} //app

extern "C" void app_run(void)
{
    app::App app;

    app.init();
    app.run();

    while (1)
        ;
}
