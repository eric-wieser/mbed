/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

#define PORT_SHIFT  3

typedef enum {
    // Pin Names
    PA_0 = 0, PA_1, PA_2, PA_3, PA_4, PA_5, PA_6, PA_7,
    PB_0 = 8, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7,
    PC_0 = 16, PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7,
    PD_0 = 24, PD_1, PD_2, PD_3, PD_4, PD_5, PD_6, PD_7,
    PE_0 = 32, PE_1, PE_2, PE_3, PE_4, PE_5,
    PF_0 = 40, PF_1, PF_2, PF_3, PF_4,

    // Not connected
    NC = (int)0xFFFFFFFF,

    LED1 = PF_2, LED4 = PF_3
} PinName;

typedef enum {
    PullNone = 0,
    PullUp = 1,
    PullDown = 2,
    OpenDrain = 3,
    PullDefault = PullDown
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
