#pragma once

#include "hw/uart/Serial.hpp"

namespace rosserial
{

class IRosserial_client
{
public:
    virtual ~IRosserial_client() = default;

    virtual void init();
    virtual int read();
    virtual void write(uint8_t* data, int length);
    virtual unsigned long time();
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
