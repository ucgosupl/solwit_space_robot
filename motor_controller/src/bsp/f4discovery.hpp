#pragma once

#include "hw/uart/Uart.hpp"
#include "hw/dma/Dma.hpp"
#include "hw/gpio/Gpio.hpp"

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

} //uart
} //hw

#define SERIAL_UART_USART_IRQ_HANDLER USART3_IRQHandler
#define SERIAL_UART_DMA_IRQ_HANDLER DMA1_Stream3_IRQHandler
