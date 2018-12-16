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

    static constexpr IRQn_Type get_base_irqn(Id id)
    {
        switch (id)
        {
        case Id::Dma1:
            return DMA1_Stream0_IRQn;
        case Id::Dma2:
            return DMA2_Stream0_IRQn;
        default:
            //assert error
            return NonMaskableInt_IRQn;
        }
    }

    static constexpr IRQn_Type calculate_irqn(Id id, Stream stream)
    {
        return static_cast<IRQn_Type>(get_base_irqn(id) + static_cast<int>(stream));
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
    , _irqn{Utils::calculate_irqn(_id, _stream)}
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

void Dma::dma_irq_handler()
{
    constexpr uint32_t DMA_SxCR_EN_bit = 0;

    if (0 != bitband_periph_get(_irq_regs._isr, _irq_regs._tcif_bit_number))
    {
        bitband_periph_set(_irq_regs._ifcr, _irq_regs._tcif_bit_number);
        bitband_periph_clear(&_dma->CR, DMA_SxCR_EN_bit);
    }
}
} //dma
} //hw
