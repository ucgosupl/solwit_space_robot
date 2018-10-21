#include "App.hpp"

namespace app
{

App::App()
{

}

void App::init()
{
    motor_drv.init();
}

void App::run()
{
    while (1)
    {
        motor_drv.move_forward(500);
        motor_drv.move_backward(500);
        motor_drv.move_left(500);
        motor_drv.move_right(500);
    }
}

}

extern "C" void app_run(void)
{
    app::App app;

    app.init();
    app.run();

    while (1)
        ;
}
