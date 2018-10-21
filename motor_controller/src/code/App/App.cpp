#include "hw/uart/Serial.hpp"

#include "App.hpp"

namespace app
{

App::App()
{

}

void App::init()
{
    __enable_irq();

    _serial_drv.init();
    _motor_drv.init();
}

void App::run()
{
    const char test_string[] = "Testowy string 123456\n";

    _serial_drv.send((uint8_t *)test_string, sizeof(test_string) - 1);

    //todo: only for test to check serial without running motors
    while (1)
        ;

    while (1)
    {
        _motor_drv.move_forward(500);
        _motor_drv.move_backward(500);
        _motor_drv.move_left(500);
        _motor_drv.move_right(500);
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
