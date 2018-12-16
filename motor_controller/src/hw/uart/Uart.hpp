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

enum class Id
{
    Usart1,
    Usart2,
    Usart3,
    Usart4,
    Usart5,
    Usart6,
};

using baudrate_t = uint32_t;

class Uart
{
public:
    Uart(gpio::Gpio *gpio,
         gpio::Pin pin_tx,
         gpio::Pin pin_rx,
         dma::Dma *dma,
         Id id
         );

    void init(baudrate_t baud);
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
    Id _id;
    USART_TypeDef * const _uart;

    void gpio_config();
    void dma_config();
    void uart_config(baudrate_t baud);

    void enable();
    void set_baudrate(baudrate_t baud);
    void irq_config(uint32_t priority);
    void peripheral_config();
};

} //uart
} //hw

