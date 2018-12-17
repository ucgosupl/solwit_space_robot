#include "Dma.hpp"

#include "hw/bitband.hpp"

namespace hw
{
namespace dma
{

class Utils
{
public:
    static constexpr uint32_t DMA_OFFSET = DMA2_BASE - DMA1_BASE;
    static constexpr uint32_t DMA_STREAM_START = DMA1_Stream0_BASE - DMA1_BASE;
    static constexpr uint32_t DMA_STREAM_OFFSET = DMA1_Stream1_BASE - DMA1_Stream0_BASE;

    static constexpr uint32_t get_base_addr(Id id)
    {
        return DMA1_BASE + DMA_OFFSET * static_cast<int>(id);
    }

    static constexpr uint32_t calculate_address(Id id, Stream stream)
    {
        return get_base_addr(id) + DMA_STREAM_START + DMA_STREAM_OFFSET * static_cast<uint32_t>(stream);
    }

    static constexpr IRQn_Type get_irqn(Id id, Stream stream)
    {
        switch (id)
        {
        case Id::Dma1:
            return get_irqn_dma1(stream);
        case Id::Dma2:
            return get_irqn_dma2(stream);
        default:
            return NonMaskableInt_IRQn;
        }
    }

    static constexpr IRQn_Type get_irqn_dma1(Stream stream)
    {
        switch (stream)
        {
        case Stream::Stream0:
            return DMA1_Stream0_IRQn;
        case Stream::Stream1:
            return DMA1_Stream1_IRQn;
        case Stream::Stream2:
            return DMA1_Stream2_IRQn;
        case Stream::Stream3:
            return DMA1_Stream3_IRQn;
        case Stream::Stream4:
            return DMA1_Stream4_IRQn;
        case Stream::Stream5:
            return DMA1_Stream5_IRQn;
        case Stream::Stream6:
            return DMA1_Stream6_IRQn;
        case Stream::Stream7:
            return DMA1_Stream7_IRQn;
        default:
            return NonMaskableInt_IRQn;
        }
    }

    static constexpr IRQn_Type get_irqn_dma2(Stream stream)
    {
        switch (stream)
        {
        case Stream::Stream0:
            return DMA2_Stream0_IRQn;
        case Stream::Stream1:
            return DMA2_Stream1_IRQn;
        case Stream::Stream2:
            return DMA2_Stream2_IRQn;
        case Stream::Stream3:
            return DMA2_Stream3_IRQn;
        case Stream::Stream4:
            return DMA2_Stream4_IRQn;
        case Stream::Stream5:
            return DMA2_Stream5_IRQn;
        case Stream::Stream6:
            return DMA2_Stream6_IRQn;
        case Stream::Stream7:
            return DMA2_Stream7_IRQn;
        default:
            return NonMaskableInt_IRQn;
        }
    }

    static constexpr uint32_t calculate_isr_address(Id id, Stream stream)
    {
        return get_base_addr(id) + (static_cast<uint32_t>(stream) >> 2) * 4;
    }

    static constexpr uint32_t calculate_ifcr_address(Id id, Stream stream)
    {
        return get_base_addr(id) + 0x08u + (static_cast<uint32_t>(stream) >> 2) * 4;
    }

    static constexpr uint32_t calculate_isr_tcif_bit(Stream stream)
    {
        switch (static_cast<int>(stream) % 4)
        {
        case 0:
            return 5;
        case 1:
            return 11;
        case 2:
            return 21;
        case 3:
            return 27;
        default:
            //assert error
            return 0;
        }
    }

    static constexpr uint32_t calculate_rcc_ahb1enr_bit(Id id)
    {
        return 21 + static_cast<int>(id);
    }
};

Dma::DmaInterruptRegs::DmaInterruptRegs(Id id, Stream stream)
    : _isr(reinterpret_cast<__IO uint32_t *>(Utils::calculate_isr_address(id, stream)))
    , _ifcr(reinterpret_cast<__IO uint32_t *>(Utils::calculate_ifcr_address(id, stream)))
    , _tcif_bit_number(Utils::calculate_isr_tcif_bit(stream))
{};

Dma::Dma(Id id, Stream stream)
    : _id{id}
    , _stream{stream}
    , _dma{reinterpret_cast<DMA_Stream_TypeDef *>(Utils::calculate_address(id, stream))}
    , _irq_regs{id, stream}
    , _irqn{Utils::get_irqn(_id, _stream)}
    , _in_progress(false)
{};

void Dma::init()
{
    bitband_periph_set(&RCC->AHB1ENR, Utils::calculate_rcc_ahb1enr_bit(_id));
}

void Dma::configure_irq(uint32_t priority)
{
    NVIC_SetPriority(_irqn, priority);
}

void Dma::enable_irq()
{
    NVIC_EnableIRQ(_irqn);
}

void Dma::bind_memory_to_peripheral(volatile void *periph_reg,
                               void *mem_reg,
                               uint32_t n_bytes,
                               Channel channel)
{
    _in_progress = true;

    _dma->PAR = reinterpret_cast<uint32_t>(periph_reg);
    _dma->M0AR = reinterpret_cast<uint32_t>(mem_reg);
    _dma->NDTR = n_bytes;

    _dma->CR = (static_cast<int>(channel) << 25)
            | (2 << 16)         // Priority high
            | DMA_SxCR_MINC     // Memory increment
            | (1 << 6)          // Memory to peripheral
            | DMA_SxCR_TCIE;    // Transfer complete interrupt enable

    _dma->CR |= DMA_SxCR_EN;
}

bool Dma::is_in_progress()
{
    return _in_progress;
}

void Dma::dma_irq_handler()
{
    constexpr uint32_t DMA_SxCR_EN_bit = 0;

    if (0 != bitband_periph_get(_irq_regs._isr, _irq_regs._tcif_bit_number))
    {
        bitband_periph_set(_irq_regs._ifcr, _irq_regs._tcif_bit_number);
        bitband_periph_clear(&_dma->CR, DMA_SxCR_EN_bit);
        _in_progress = false;
    }
}
} //dma
} //hw
