#include "Uart.hpp"

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
           DMA_Stream_TypeDef *dma)
        : _gpio{gpio}
        , _pin_tx{pin_tx}
        , _pin_rx{pin_rx}
        , _uart{uart}
        , _dma{dma}
{
}

void Uart::init()
{
    // Initialize GPIOs
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    gpio_mode_config(_gpio, _pin_tx, GPIO_MODE_AF);
    gpio_mode_config(_gpio, _pin_rx, GPIO_MODE_AF);
    gpio_af_config(_gpio, _pin_tx, GPIO_AF_USART3);
    gpio_af_config(_gpio, _pin_rx, GPIO_AF_USART3);

    // Initialize DMA
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    NVIC_SetPriority(DMA1_Stream3_IRQn, DMA_PRIORITY);
    NVIC_EnableIRQ(DMA1_Stream3_IRQn);

    // Initialize USART peripheral
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    _uart->BRR = APB1_CLOCK_FREQ / UART_BAUD_RATE;

    NVIC_SetPriority(USART3_IRQn, UART_PRIORITY);
    NVIC_EnableIRQ(USART3_IRQn);

    _uart->CR3 = USART_CR3_DMAT;
    _uart->CR1 = USART_CR1_RXNEIE | USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
}

int32_t Uart::send_buf(uint8_t *buf, int32_t n_bytes)
{
    if ((buf == nullptr) || (n_bytes < 1)) {
        // Invalid arguments
        return -1;
    }

    //todo: return busy

    //setup dma
    _dma->PAR = (uint32_t) &_uart->DR;
    _dma->M0AR = (uint32_t)buf;
    _dma->NDTR = n_bytes;

    _dma->CR = (4 << 25)        // Channel 4
            | (2 << 16)         // Priority high
            | DMA_SxCR_MINC     // Memory increment
            | (1 << 6)          // Memory to peripheral
            | DMA_SxCR_TCIE;    // Transfer complete interrupt enable

    _dma->CR |= DMA_SxCR_EN;

    return 0;
}

bool Uart::is_rx_pending()
{
    return ! !(_uart->SR & USART_SR_RXNE);
}

uint8_t Uart::read_byte()
{
    return (uint8_t)_uart->DR;
}

void Uart::uart_irq_handler()
{
    if (is_rx_pending()) {
        auto data = read_byte();
    }
}

void Uart::dma_irq_handler()
{
    auto lisr = DMA1->LISR;

    if (0 != (lisr & DMA_LISR_TCIF3))
    {
        /* Clear transfer complete flag and DMA enable flag */
        DMA1->LIFCR |= DMA_LIFCR_CTCIF3;
        _dma->CR &= ~(DMA_SxCR_EN);
    }
}

} //uart
} //hw

