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
#include "gpio_api.h"
#include "pinmap.h"

uint32_t gpio_set(PinName pin) {
    uint32_t port_index = (uint32_t) pin >> 3;

    // Enable GPIO peripheral clock
    SYSCTL->RCGC2 |= 1 << port_index;

    return 1 << ((uint32_t) pin & 0x7);
}

void gpio_init(gpio_t *obj, PinName pin, PinDirection direction) {
    if(pin == NC) return;

    obj->pin = pin;
    obj->mask = gpio_set(pin);

    uint32_t port_index = (uint32_t) pin >> 3;

    switch(port_index) {
        case PortA: obj->regs = GPIOA; break;
        case PortB: obj->regs = GPIOB; break;
        case PortC: obj->regs = GPIOC; break;
        case PortD: obj->regs = GPIOD; break;
        case PortE: obj->regs = GPIOE; break;
        case PortF: obj->regs = GPIOF; break;
    }

    gpio_dir(obj, direction);

    switch (direction) {
        case PIN_OUTPUT: gpio_mode(obj, PullNone); break;
        case PIN_INPUT : gpio_mode(obj, PullDown); break;
    }

    obj->regs->DEN |= obj->mask;
}

void gpio_mode(gpio_t *obj, PinMode mode) {
    if(mode ==OpenDrain) obj->regs->ODR |= obj->mask;
    else                 obj->regs->ODR &= ~obj->mask;
    if(mode == PullUp)   obj->regs->PUR |= obj->mask;
    else                 obj->regs->PUR &= ~obj->mask;
    if(mode == PullDown) obj->regs->PDR |= obj->mask;
    else                 obj->regs->PDR &= ~obj->mask;
}

void gpio_dir(gpio_t *obj, PinDirection direction) {
    switch (direction) {
        case PIN_INPUT : obj->regs->DIR &= ~obj->mask; break;
        case PIN_OUTPUT: obj->regs->DIR |=  obj->mask; break;
    }
}
