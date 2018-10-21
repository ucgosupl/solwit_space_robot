#pragma once

#include "Uart.hpp"

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
    Uart _drv;
};

} //uart
} //hw
