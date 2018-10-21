#pragma once

namespace hw
{
namespace uart
{

class Uart;

class Utility
{
public:
    static void driver_set(Uart *drv);
    static void uart_irq_handler();
    static void dma_irq_handler();

private:
    static Uart *_drv;
};

} //uart
} //hw
