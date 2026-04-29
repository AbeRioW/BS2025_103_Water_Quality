#ifndef __THRESHOLD_H
#define __THRESHOLD_H

#include "stm32f1xx_hal.h"

#define FLASH_USER_START_ADDR   0x08007000
#define FLASH_USER_END_ADDR     0x08007FFF

#define DEFAULT_TUR_THRESHOLD   3000
#define DEFAULT_TMP_THRESHOLD   20
#define DEFAULT_PH_THRESHOLD    1

typedef struct {
    uint32_t turbidity;
    uint16_t temperature;
    uint16_t ph;
} ThresholdTypeDef;

extern ThresholdTypeDef thresholds;

void Threshold_Init(void);
HAL_StatusTypeDef Threshold_SaveToFlash(void);
HAL_StatusTypeDef Threshold_LoadFromFlash(void);
void Threshold_SetTurbidity(uint32_t value);
void Threshold_SetTemperature(uint16_t value);
void Threshold_SetPH(uint16_t value);

#endif