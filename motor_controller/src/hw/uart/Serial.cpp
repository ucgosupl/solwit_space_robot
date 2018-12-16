
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

/** GPIO port used */
constexpr gpio::Port SERIAL_UART_GPIO_PORT = gpio::Port::B;
/** Pin number used for USART TX - PB10. */
constexpr gpio::Pin SERIAL_UART_TX_PIN = gpio::Pin::P10;
/** Pin number used for USART RX - PB11. */
constexpr gpio::Pin SERIAL_UART_RX_PIN = gpio::Pin::P11;

/** DMA id used by USART TX. */
constexpr dma::Id SERIAL_UART_TX_DMA_ID = dma::Id::Dma1;
/** DMA stream used by USART TX. */
constexpr dma::Stream SERIAL_UART_TX_DMA_STREAM = dma::Stream::Stream3;
/** DMA channel used by USART TX. */
constexpr dma::Channel SERIAL_UART_TX_DMA_CHANNEL = dma::Channel::Channel4;

constexpr uart::Id SERIAL_UART_ID = uart::Id::Usart3;

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
