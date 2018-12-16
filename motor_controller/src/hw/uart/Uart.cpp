#include "Uart.hpp"

#include "hw/bitband.hpp"

namespace hw
{
namespace uart
{

/** USART baud rate. */
constexpr uint32_t UART_BAUD_RATE = 115200;

constexpr uint32_t DMA_PRIORITY = 4;
constexpr uint32_t UART_PRIORITY = 5;

Uart::Uart(GPIO_TypeDef *gpio,
           uint32_t pin_tx,
           uint32_t pin_rx,
           USART_TypeDef *uart,
           dma::Dma *dma)
        : _gpio{gpio}
        , _pin_tx{pin_tx}
        , _pin_rx{pin_rx}
        , _uart{uart}
        , _dma{dma}
{
}

void Uart::init()
{
    gpio_init();
    dma_init();
    usart_init();
}

void Uart::gpio_init()
{
    constexpr uint32_t RCC_AHB1ENR_GPIOBEN_bit = 1;

    bitband_periph_set(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN_bit);
    gpio_mode_config(_gpio, _pin_tx, GPIO_MODE_AF);
    gpio_mode_config(_gpio, _pin_rx, GPIO_MODE_AF);
    gpio_af_config(_gpio, _pin_tx, GPIO_AF_USART3);
    gpio_af_config(_gpio, _pin_rx, GPIO_AF_USART3);
}

void Uart::dma_init()
{
    _dma->init();
    _dma->configure_irq(DMA_PRIORITY);
    _dma->enable_irq();
}

void Uart::usart_init()
{
    constexpr uint32_t RCC_APB1ENR_USART3EN_bit = 18;

    bitband_periph_set(&RCC->APB1ENR, RCC_APB1ENR_USART3EN_bit);
    _uart->BRR = APB1_CLOCK_FREQ / UART_BAUD_RATE;

    NVIC_SetPriority(USART3_IRQn, UART_PRIORITY);
    NVIC_EnableIRQ(USART3_IRQn);

    _uart->CR3 = USART_CR3_DMAT;
    _uart->CR1 = USART_CR1_RXNEIE | USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
}

int32_t Uart::send_buf(uint8_t *buf, int32_t n_bytes, dma::Channel channel)
{
    if ((buf == nullptr) || (n_bytes < 1))
    {
        // Invalid arguments
        return -1;
    }

    //todo: return busy

    _dma->bind_memory_to_peripheral(&_uart->DR, buf, n_bytes, channel);

    return 0;
}

bool Uart::is_rx_pending()
{
    constexpr uint32_t USART_SR_RXNE_bit = 5;

    return bitband_periph_get(&_uart->SR, USART_SR_RXNE_bit) == 1;
}

uint8_t Uart::read_byte()
{
    return (uint8_t)_uart->DR;
}

void Uart::uart_irq_handler()
{
    if (is_rx_pending())
    {
        //data is unused for now it is read only to clear a flag
        auto data = read_byte();
        (void)data;
    }
}

void Uart::dma_irq_handler()
{
    _dma->dma_irq_handler();
}

} //uart
} //hw

