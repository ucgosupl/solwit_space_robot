#pragma once

extern "C"
{
#include "platform_specific.h"
#include "hw/gpio/gpio_f4.h"
}

#include "hw/dma/Dma.hpp"
#include "hw/gpio/Gpio.hpp"

namespace hw
{
namespace uart
{

class Uart
{
public:
    Uart(gpio::Gpio *gpio,
         gpio::Pin pin_tx,
         gpio::Pin pin_rx,
         dma::Dma *dma,
         USART_TypeDef *uart
         );

    void init();
    int32_t send_buf(uint8_t *buf, int32_t n_bytes, dma::Channel channel);
    bool is_rx_pending();
    uint8_t read_byte();
    void uart_irq_handler();
    void dma_irq_handler();

private:
    gpio::Gpio * const _gpio;
    gpio::Pin _pin_tx;
    gpio::Pin _pin_rx;
    dma::Dma * const _dma;
    USART_TypeDef * const _uart;

    void gpio_config();
    void dma_config();
    void uart_config();
};

} //uart
} //hw

