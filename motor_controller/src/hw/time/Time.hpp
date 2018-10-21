#pragma once

#include <cstdint>

namespace hw
{
namespace time
{

using time_t = std::int32_t;

void time_init();
time_t ms_get();
void delay(time_t ms);

} //time
} //hw
