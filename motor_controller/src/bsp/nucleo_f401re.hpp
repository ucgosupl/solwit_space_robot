#pragma once

namespace hw
{
namespace uart
{
//todo: change all values to nucleo
/** GPIO port used */
constexpr gpio::Port SERIAL_UART_GPIO_PORT = gpio::Port::A;
/** Pin number used for USART TX */
constexpr gpio::Pin SERIAL_UART_TX_PIN = gpio::Pin::P11;
/** Pin number used for USART RX */
constexpr gpio::Pin SERIAL_UART_RX_PIN = gpio::Pin::P12;

/** DMA id used by USART TX. */
constexpr dma::Id SERIAL_UART_TX_DMA_ID = dma::Id::Dma2;
/** DMA stream used by USART TX. */
constexpr dma::Stream SERIAL_UART_TX_DMA_STREAM = dma::Stream::Stream6;
/** DMA channel used by USART TX. */
constexpr dma::Channel SERIAL_UART_TX_DMA_CHANNEL = dma::Channel::Channel5;

constexpr uart::Id SERIAL_UART_ID = uart::Id::Usart6;

} //uart
} //hw

#define SERIAL_UART_USART_IRQ_HANDLER USART6_IRQHandler
#define SERIAL_UART_DMA_IRQ_HANDLER DMA2_Stream6_IRQHandler
