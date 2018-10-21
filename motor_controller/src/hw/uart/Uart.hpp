#pragma once

extern "C"
{
#include "platform_specific.h"
#include "hw/gpio_f4/gpio_f4.h"
}

namespace hw
{
namespace uart
{

class Uart
{
public:
    Uart(GPIO_TypeDef *gpio,
           uint32_t pin_tx,
           uint32_t pin_rx,
           USART_TypeDef *uart,
           DMA_Stream_TypeDef *dma);

    void init();
    int32_t send_buf(uint8_t *buf, int32_t n_bytes);
    bool is_rx_pending();
    uint8_t read_byte();
    void uart_irq_handler();
    void dma_irq_handler();

private:
    GPIO_TypeDef * const _gpio;
    const uint32_t _pin_tx;
    const uint32_t _pin_rx;
    USART_TypeDef * const _uart;
    DMA_Stream_TypeDef * const _dma;
};

} //uart
} //hw

