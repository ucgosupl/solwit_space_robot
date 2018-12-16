
extern "C"
{
#include "platform_specific.h"
#include "hw/gpio/gpio_f4.h"
}

#include "Uart.hpp"
#include "Utility.hpp"

#include "Serial.hpp"

#include "bsp/board.hpp"

namespace hw
{
namespace uart
{

Serial::Serial()
    : _dma(SERIAL_UART_TX_DMA_ID, SERIAL_UART_TX_DMA_STREAM)
    , _gpio(SERIAL_UART_GPIO_PORT)
    , _drv{&_gpio,
           SERIAL_UART_TX_PIN,
           SERIAL_UART_RX_PIN,
           &_dma,
           SERIAL_UART_ID
           }
{

}

void Serial::init()
{
    Utility::driver_set(&_drv);
    _drv.init(SERIAL_UART_BAUD_RATE);
}

int Serial::send(uint8_t *buf, int32_t n_bytes)
{
    return _drv.send_buf(buf, n_bytes, SERIAL_UART_TX_DMA_CHANNEL);
}

int Serial::recv()
{
    //check ready
    //read byte
    //return byte or error
}

}   //uart
}   //hw
