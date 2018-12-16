#pragma once

#include "Uart.hpp"
#include "hw/dma/Dma.hpp"
#include "hw/gpio/Gpio.hpp"

namespace hw
{
namespace uart
{

/** USART baud rate. */
constexpr uint32_t SERIAL_UART_BAUD_RATE = 115200;
class Serial
{
public:
    Serial();

    void init();
    int send(uint8_t *buf, int32_t n_bytes);
    int recv();

private:
    //for now devices are bound to serial,but for shared devices like dma and
    //gpio it may be problematic. It could be better to obtain them somehow
    //from global device controller.
    dma::Dma _dma;
    gpio::Gpio _gpio;
    Uart _drv;
};

} //uart
} //hw
