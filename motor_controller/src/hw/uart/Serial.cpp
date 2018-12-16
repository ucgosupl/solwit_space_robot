
extern "C"
{
#include "platform_specific.h"
#include "hw/gpio/gpio_f4.h"
}

#include "Uart.hpp"
#include "Utility.hpp"

#include "Serial.hpp"

namespace hw
{
namespace uart
{

/** Pin number used for USART TX - PB10. */
constexpr uint32_t UART_TX_PIN = 10;
/** Pin number used for USART RX - PB11. */
constexpr uint32_t UART_RX_PIN = 11;
/** DMA Stream used by USART TX. */
#define UART_DMA DMA1_Stream3

Serial::Serial()
    : _dma(dma::Id::Dma1, dma::Stream::Stream3)
    , _drv{GPIOB,
            UART_TX_PIN,
            UART_RX_PIN,
            USART3,
            &_dma}
{

}

void Serial::init()
{
    Utility::driver_set(&_drv);
    _drv.init();
}

int Serial::send(uint8_t *buf, int32_t n_bytes)
{
    return _drv.send_buf(buf, n_bytes, dma::Channel::Channel4);
}

int Serial::recv()
{
    //check ready
    //read byte
    //return byte or error
}

}   //uart
}   //hw
