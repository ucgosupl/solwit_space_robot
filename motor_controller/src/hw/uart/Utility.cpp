#include "Uart.hpp"
#include "Utility.hpp"

#include "bsp/board.hpp"

namespace hw
{
namespace uart
{

Uart *Utility::_drv = nullptr;

void Utility::driver_set(Uart *drv)
{
    _drv = drv;
}

void Utility::uart_irq_handler()
{
    if (nullptr != _drv)
    {
        _drv->uart_irq_handler();
    }
}

void Utility::dma_irq_handler()
{
    if (nullptr != _drv)
    {
        _drv->dma_irq_handler();
    }
}

} //uart
} //hw

extern "C" void SERIAL_UART_USART_IRQ_HANDLER(void)
{
    hw::uart::Utility::uart_irq_handler();
}

extern "C" void SERIAL_UART_DMA_IRQ_HANDLER(void)
{
    hw::uart::Utility::dma_irq_handler();
}
