#include "threshold.h"

ThresholdTypeDef thresholds;

void Threshold_Init(void)
{
    if(Threshold_LoadFromFlash() != HAL_OK)
    {
        thresholds.turbidity = DEFAULT_TUR_THRESHOLD;
        thresholds.temperature = DEFAULT_TMP_THRESHOLD;
        thresholds.ph = DEFAULT_PH_THRESHOLD;
        Threshold_SaveToFlash();
    }
}

HAL_StatusTypeDef Threshold_LoadFromFlash(void)
{
    uint32_t *flash_data = (uint32_t *)FLASH_USER_START_ADDR;
    
    if(flash_data[0] == 0xFFFFFFFF || flash_data[1] == 0xFFFFFFFF || flash_data[2] == 0xFFFFFFFF)
    {
        return HAL_ERROR;
    }
    
    thresholds.turbidity = flash_data[0];
    thresholds.temperature = (uint16_t)flash_data[1];
    thresholds.ph = (uint16_t)flash_data[2];
    
    return HAL_OK;
}

HAL_StatusTypeDef Threshold_SaveToFlash(void)
{
    HAL_StatusTypeDef status = HAL_OK;
    FLASH_EraseInitTypeDef erase_init;
    uint32_t page_error = 0;
    
    erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
    erase_init.PageAddress = FLASH_USER_START_ADDR;
    erase_init.NbPages = 1;
    
    HAL_FLASH_Unlock();
    
    status = HAL_FLASHEx_Erase(&erase_init, &page_error);
    if(status != HAL_OK)
    {
        HAL_FLASH_Lock();
        return status;
    }
    
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_USER_START_ADDR, thresholds.turbidity);
    if(status != HAL_OK)
    {
        HAL_FLASH_Lock();
        return status;
    }
    
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_USER_START_ADDR + 4, thresholds.temperature);
    if(status != HAL_OK)
    {
        HAL_FLASH_Lock();
        return status;
    }
    
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_USER_START_ADDR + 8, thresholds.ph);
    
    HAL_FLASH_Lock();
    
    return status;
}

void Threshold_SetTurbidity(uint32_t value)
{
    thresholds.turbidity = value;
    Threshold_SaveToFlash();
}

void Threshold_SetTemperature(uint16_t value)
{
    thresholds.temperature = value;
    Threshold_SaveToFlash();
}

void Threshold_SetPH(uint16_t value)
{
    thresholds.ph = value;
    Threshold_SaveToFlash();
}