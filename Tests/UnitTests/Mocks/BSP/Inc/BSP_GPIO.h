
#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "common.h"
#include "fff.h"


typedef enum {PORTA = 0, PORTB, PORTC, PORTD, NUM_PORTS} port_t; 
typedef enum {INPUT = 0, OUTPUT} direction_t;

DECLARE_FAKE_VOID_FUNC(BSP_GPIO_Init, port_t, uint16_t, direction_t);

DECLARE_FAKE_VALUE_FUNC(uint16_t, BSP_GPIO_Read, port_t);

DECLARE_FAKE_VOID_FUNC(BSP_GPIO_Write, port_t, uint16_t);

DECLARE_FAKE_VALUE_FUNC(uint8_t, BSP_GPIO_Read_Pin, port_t, uint16_t);

DECLARE_FAKE_VOID_FUNC(BSP_GPIO_Write_Pin, port_t, uint16_t, bool);

DECLARE_FAKE_VALUE_FUNC(uint8_t, BSP_GPIO_Get_State, port_t, uint16_t);


#endif


/* @} */