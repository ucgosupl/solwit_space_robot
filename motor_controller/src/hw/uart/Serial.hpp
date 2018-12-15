#pragma once

#include "Uart.hpp"
#include "hw/dma/Dma.hpp"

namespace hw
{
namespace uart
{

class Serial
{
public:
    Serial();

    void init();
    int send(uint8_t *buf, int32_t n_bytes);
    int recv();

private:
    dma::Dma _dma;
    Uart _drv;
};

} //uart
} //hw
