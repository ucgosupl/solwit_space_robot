#include "Stm32_client.hpp"

namespace rosserial
{

Stm32_client::Stm32_client()
{

}

void Stm32_client::init()
{
    _serial_drv.init();
}

int Stm32_client::read()
{
    return _serial_drv.recv();
}

void Stm32_client::write(uint8_t* data, int length)
{
    _serial_drv.send(data, static_cast<uint32_t>(length));
}

unsigned long Stm32_client::time()
{
    return 0;
}

}
