#ifndef __DS18B20_H
#define __DS18B20_H

#include "stdint.h"
#include "gpio.h"

#define DS18B20_DQ_Clr()  HAL_GPIO_WritePin(DS18B20_GPIO_Port, DS18B20_Pin, GPIO_PIN_RESET)
#define DS18B20_DQ_Set()  HAL_GPIO_WritePin(DS18B20_GPIO_Port, DS18B20_Pin, GPIO_PIN_SET)
#define DS18B20_DQ_Read() HAL_GPIO_ReadPin(DS18B20_GPIO_Port, DS18B20_Pin)

void DS18B20_Init(void);
float DS18B20_Get_Temp(void);

#endif
