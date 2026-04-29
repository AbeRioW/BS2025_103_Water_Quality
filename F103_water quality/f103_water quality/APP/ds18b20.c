#include "ds18b20.h"

// 微秒级延时函数
void delay_us(uint32_t us)
{
    uint32_t i;
    for(i=0; i<us*8; i++);
}

// 初始化DS18B20
void DS18B20_Init(void)
{
    DS18B20_DQ_Set();
    delay_us(10);
    DS18B20_DQ_Clr();
    delay_us(960);
    DS18B20_DQ_Set();
    delay_us(60);
    DS18B20_DQ_Read();
    delay_us(960);
}

// 读一位
uint8_t DS18B20_Read_Bit(void)
{
    uint8_t dat = 0;
    DS18B20_DQ_Clr();
    delay_us(1);
    DS18B20_DQ_Set();
    delay_us(9);
    dat = DS18B20_DQ_Read();
    delay_us(100);
    DS18B20_DQ_Set();
    delay_us(4);
    return dat;
}

// 写一位
void DS18B20_Write_Bit(uint8_t dat)
{
    DS18B20_DQ_Clr();
    delay_us(1);
    if(dat & 0x01) DS18B20_DQ_Set();
    else DS18B20_DQ_Clr();
    delay_us(118);
    DS18B20_DQ_Set();
    delay_us(4);
}

// 写一个字节
void DS18B20_Write_Byte(uint8_t dat)
{
    uint8_t i;
    for(i=0; i<8; i++)
    {
        DS18B20_Write_Bit(dat & 0x01);
        dat >>= 1;
    }
}

// 读一个字节
uint8_t DS18B20_Read_Byte(void)
{
    uint8_t i, dat=0;
    for(i=0; i<8; i++)
    {
        dat >>= 1;
        if(DS18B20_Read_Bit()) dat |= 0x80;
    }
    DS18B20_DQ_Set();
    return dat;
}

// 获取温度
float DS18B20_Get_Temp(void)
{
    uint8_t temp_l, temp_h;
    int16_t temp;
    float temperature;
    
    DS18B20_Init();
    DS18B20_Write_Byte(0xCC);
    DS18B20_Write_Byte(0x44);
    
    DS18B20_Init();
    DS18B20_Write_Byte(0xCC);
    DS18B20_Write_Byte(0xBE);
    
    temp_l = DS18B20_Read_Byte();
    temp_h = DS18B20_Read_Byte();
    
    temp = (temp_h << 8) | temp_l;
    
    if(temp < 0)
    {
        temperature = (float)(temp & 0x7FFF) / 16.0;
        temperature = -temperature;
    }
    else
    {
        temperature = (float)temp / 16.0;
    }
    
    return temperature;
}
