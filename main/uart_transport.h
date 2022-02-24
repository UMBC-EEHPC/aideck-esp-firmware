/**
 * ,---------,       ____  _ __
 * |  ,-^-,  |      / __ )(_) /_______________ _____  ___
 * | (  O  ) |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * | / ,--´  |    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *    +------`   /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * ESP deck firmware
 *
 * Copyright (C) 2022 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// The UART transport module represents the transport link between the router and the STM on the Crazyflie.

#include <stdint.h>
#include <stddef.h>
#include "cpx.h"

#define UART_TRANSPORT_MTU 100

#if UART_TRANSPORT_MTU > CPX_MAX_PAYLOAD_SIZE
    #pragma warn "UART MTU bigger than defined by CPX"
#endif


typedef struct {
    CPXRoutingPacked_t route;
    uint8_t data[UART_TRANSPORT_MTU - CPX_ROUTING_PACKED_SIZE];
} __attribute__((packed)) uartTransportPayload_t;

typedef struct {
    uint8_t start;
    uint8_t payloadLength;
    union {
        uartTransportPayload_t routablePayload;
        uint8_t payload[UART_TRANSPORT_MTU];
    };
} __attribute__((packed)) uart_transport_packet_t;


void uart_transport_init();

// Interface used by the router
void uart_transport_send(const CPXRoutablePacket_t* packet);
void uart_transport_receive(CPXRoutablePacket_t* packet);
