#pragma once

#include "platform_specific.h"

namespace hw
{
namespace dma
{

enum class Id
{
    Dma1,
    Dma2,
};

enum class Stream
{
    Stream0,
    Stream1,
    Stream2,
    Stream3,
    Stream4,
    Stream5,
    Stream6,
    Stream7,
};

enum class Channel
{
    Channel0,
    Channel1,
    Channel2,
    Channel3,
    Channel4,
    Channel5,
    Channel6,
    Channel7,
};

class Dma
{
private:
    struct DmaInterruptRegs
    {
        volatile uint32_t *_isr;
        volatile uint32_t *_ifcr;
        uint32_t _tcif_bit_number;

        DmaInterruptRegs(Id id, Stream stream);
    };

public:
    Dma(Id id, Stream stream);

    void init();
    void configure_irq(uint32_t priority);
    void enable_irq();
    void bind_memory_to_peripheral(volatile void *periph_reg,
                                   void *mem_reg,
                                   uint32_t n_bytes,
                                   Channel channel);
    void dma_irq_handler();
    bool is_in_progress();

private:
    Id _id;
    Stream _stream;
    DMA_Stream_TypeDef * const _dma;
    DmaInterruptRegs _irq_regs;
    IRQn_Type _irqn;
    bool _in_progress;
};

} //dma
} //hw
