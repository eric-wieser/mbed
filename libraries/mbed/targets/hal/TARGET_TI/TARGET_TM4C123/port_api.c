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
#include "port_api.h"
#include "pinmap.h"
#include "gpio_api.h"

#if DEVICE_PORTIN || DEVICE_PORTOUT

PinName port_pin(PortName port, int pin_n) {
    return pin_n + (port << 3);
}

void port_init(port_t *obj, PortName port, int mask, PinDirection dir) {
    obj->port = port;
    obj->mask = mask;

    uint32_t port_index = (uint32_t) port;

    // Enable GPIO peripheral clock
    SYSCTL->RCGC2 |= 1 << port_index;

    obj->regs = (GPIOA_Type *)(GPIOA_BASE + (port_index << 12));

    port_dir(obj, dir);
}

void port_mode(port_t *obj, PinMode mode) {
    if(mode == PinMode::OpenDrain) obj->regs.ODR |= obj->mask;
    else                           obj->regs.ODR &= ~obj->mask;
    if(mode == PinMode::PullUp)    obj->regs.PUR |= obj->mask;
    else                           obj->regs.PUR &= ~obj->mask;
    if(mode == PinMode::PullDown)  obj->regs.PDR |= obj->mask;
    else                           obj->regs.PDR &= ~obj->mask;

}

void port_dir(port_t *obj, PinDirection dir) {
    switch (dir) {
        case PIN_INPUT : *obj->regs.DIR &= ~obj->mask; break;
        case PIN_OUTPUT: *obj->regs.DIR |=  obj->mask; break;
    }
}

int port_read(port_t *obj) {
    return *obj->regs.DATA & obj->mask;
}

#endif
