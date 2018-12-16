/*
 * file:	board.hpp
 * author:	GAndaLF
 * brief:	Short file description.
 */

#pragma once

#ifdef __cplusplus

#if BOARD==F4DISCOVERY
#include "f4discovery.hpp"

#elif BOARD==NUCLEO_F401RE
#include "nucleo_f401re.hpp"

#else
#error "Board not specified!"
#endif //BOARD

#endif //__cplusplus
