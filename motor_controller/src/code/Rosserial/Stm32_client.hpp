#pragma once

#include "hw/uart/Serial.hpp"

namespace rosserial
{

class IRosserial_client
{
public:
    virtual ~IRosserial_client() = default;

    virtual void init() = 0;
    virtual int read() = 0;
    virtual void write(uint8_t* data, int length) = 0;
    virtual unsigned long time() = 0;
};

class Stm32_client : public IRosserial_client
{
public:
    Stm32_client();
    virtual ~Stm32_client() = default;

    void init() override;
    int read() override;
    void write(uint8_t* data, int length) override;
    unsigned long time() override;

private:
    hw::uart::Serial _serial_drv;
};

} //rosserial
