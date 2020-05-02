/*
 * Copyright (c) 2020 Piotr Stolarz
 * OneWireNg: Ardiono 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#ifndef __OWNG_DELAY_HALF_US__
#define __OWNG_DELAY_HALF_US__

#include "Arduino.h"

#define CPU_CYCLES_PER_US (F_CPU / 1000000L)

/**
 * Primitive, Arduino-specific half-microsecond delay routine.
 */
#if (CPU_CYCLES_PER_US < 2)
# define delayHalfUs()
#else
inline void delayHalfUs()
{
    register volatile int cn = 1; /* 1 cycle */
# if (CPU_CYCLES_PER_US <= 3)
# elif (CPU_CYCLES_PER_US <= 5)
    cn++; /* +1 cycle */
# elif (CPU_CYCLES_PER_US <= 7)
    cn++;
    cn++; /* +2 cycles */
# elif (CPU_CYCLES_PER_US <= 9)
    cn++;
    cn++;
    cn++; /* +3 cycles */
# elif (CPU_CYCLES_PER_US <= 11)
    cn++;
    cn++;
    cn++;
    cn++; /* +4 cycles */
# elif (CPU_CYCLES_PER_US <= 13)
    cn++;
    cn++;
    cn++;
    cn++;
    cn++; /* +5 cycles */
# elif (CPU_CYCLES_PER_US <= 15)
    cn++;
    cn++;
    cn++;
    cn++;
    cn++;
    cn++; /* +6 cycles */
# elif (CPU_CYCLES_PER_US <= 17)
    cn++;
    cn++;
    cn++;
    cn++;
    cn++;
    cn++;
    cn++; /* +7 cycles */
# else
    const int end = CPU_CYCLES_PER_US/2; /* +1 cycle */
    cn += 4;                             /* +1 cycle */
sloop:
    if (cn < end) goto eloop;            /* +2 cycles */
    cn += 4;                             /* +1 cycle */
    goto sloop;                          /* +1 cycle */
eloop:;
# endif
}
#endif

#endif /* __OWNG_DELAY_HALF_US__ */
