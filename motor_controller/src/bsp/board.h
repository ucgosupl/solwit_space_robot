#pragma once

#if BOARD==F4DISCOVERY
#include "f4discovery.h"

#elif BOARD==NUCLEO_F401RE
#include "nucleo_f401re.h"

#else
#error "Board not specified!"
#endif //BOARD

