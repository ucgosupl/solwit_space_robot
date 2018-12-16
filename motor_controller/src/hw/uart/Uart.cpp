#include "Uart.hpp"

#include "hw/bitband.hpp"

namespace hw
{
namespace uart
{

constexpr uint32_t DMA_PRIORITY = 4;
constexpr uint32_t UART_PRIORITY = 5;

class Utils
{
public:
    static constexpr uint32_t calculate_address(Id id)
    {
        switch (id)
        {
        case Id::Usart1:
            return USART1_BASE;
        case Id::Usart2:
            return USART2_BASE;
        case Id::Usart3:
            return USART3_BASE;
        case Id::Usart4:
            return UART4_BASE;
        case Id::Usart5:
            return UART5_BASE;
        case Id::Usart6:
            return USART6_BASE;
        default:
            //report error
            return 0;
        }
    }

    static constexpr volatile uint32_t * apbenr_address_get(Id id)
    {
        switch (id)
        {
        case Id::Usart1:
            return &RCC->APB2ENR;
        case Id::Usart2:
            return &RCC->APB1ENR;
        case Id::Usart3:
            return &RCC->APB1ENR;
        case Id::Usart4:
            return &RCC->APB1ENR;
        case Id::Usart5:
            return &RCC->APB1ENR;
        case Id::Usart6:
            return &RCC->APB2ENR;
        default:
            return nullptr;
        }
    }

    static constexpr uint32_t calculate_apbenr_usarten_bit(Id id)
    {
        switch (id)
        {
        case Id::Usart1:
            return 4;
        case Id::Usart2:
            return 17;
        case Id::Usart3:
            return 18;
        case Id::Usart4:
            return 19;
        case Id::Usart5:
            return 20;
        case Id::Usart6:
            return 5;
        default:
            return 0;
        }
    }

    static constexpr uint32_t apb_clock_freq_get(Id id)
    {
        switch (id)
        {
        case Id::Usart1:
        case Id::Usart6:
            return APB2_CLOCK_FREQ;
        case Id::Usart2:
        case Id::Usart3:
        case Id::Usart4:
        case Id::Usart5:
            return APB1_CLOCK_FREQ;
        default:
            return 0;
        }
    }

    static constexpr IRQn_Type irqn_get(Id id)
    {
        switch (id)
        {
        case Id::Usart1:
        case Id::Usart2:
        case Id::Usart3:
            return static_cast<IRQn_Type>(USART1_IRQn + static_cast<int>(id));
        case Id::Usart4:
        case Id::Usart5:
            return static_cast<IRQn_Type>(UART4_IRQn + static_cast<int>(id) - 3);
        case Id::Usart6:
            return USART6_IRQn;
        default:
            //report error
            return NonMaskableInt_IRQn;
        }
    }

    static constexpr uint32_t gpio_alternative_function_get(Id id)
    {
        switch (id)
        {
        case Id::Usart1:
            return GPIO_AF_USART1;
        case Id::Usart2:
            return GPIO_AF_USART2;
        case Id::Usart3:
            return GPIO_AF_USART3;
        case Id::Usart4:
            return GPIO_AF_UART4;
        case Id::Usart5:
            return GPIO_AF_UART5;
        case Id::Usart6:
            return GPIO_AF_USART6;
        default:
            //report error
            return 0;
        }
    }
};

Uart::Uart(gpio::Gpio *gpio,
           gpio::Pin pin_tx,
           gpio::Pin pin_rx,
           dma::Dma *dma,
           Id id
           )
        : _gpio{gpio}
        , _pin_tx{pin_tx}
        , _pin_rx{pin_rx}
        , _dma{dma}
        , _id{id}
        , _uart{reinterpret_cast<USART_TypeDef *>(Utils::calculate_address(id))}
{
}

void Uart::init(baudrate_t baud)
{
    gpio_config();
    dma_config();
    uart_config(baud);
}

void Uart::gpio_config()
{
    _gpio->init();
    _gpio->pin_alternative_mode_config(_pin_tx, Utils::gpio_alternative_function_get(_id));
    _gpio->pin_alternative_mode_config(_pin_rx, Utils::gpio_alternative_function_get(_id));
}

void Uart::dma_config()
{
    _dma->init();
    _dma->configure_irq(DMA_PRIORITY);
    _dma->enable_irq();
}

void Uart::uart_config(baudrate_t baud)
{
    enable();
    set_baudrate(baud);
    irq_config(UART_PRIORITY);
    peripheral_config();
}

void Uart::enable()
{
    bitband_periph_set(Utils::apbenr_address_get(_id), Utils::calculate_apbenr_usarten_bit(_id));
}

void Uart::set_baudrate(uint32_t baud)
{
    _uart->BRR = Utils::apb_clock_freq_get(_id) / baud;
}

void Uart::irq_config(uint32_t priority)
{
    NVIC_SetPriority(Utils::irqn_get(_id), priority);
    NVIC_EnableIRQ(Utils::irqn_get(_id));
}

void Uart::peripheral_config()
{
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

