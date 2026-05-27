#include "sht.h"

extern I2C_HandleTypeDef hi2c1;

// HAL koristi 8-bit adresu (shift levo 1)

void SHT_Init()
{
    uint8_t cmd = SoftReset;
    HAL_I2C_Master_Transmit(&hi2c1,  Adresa, &cmd, 1, 100);
    HAL_Delay(20);
}

void SHT_ReadReg(uint8_t *value)
{
    uint8_t cmd = ReadCmd;

    HAL_I2C_Master_Transmit(&hi2c1, Adresa, &cmd, 1, 100);
    HAL_I2C_Master_Receive(&hi2c1, Adresa, value, 1, 100);
}

void SHT_WriteReg(uint8_t value)
{
    uint8_t buf[2] = { WriteCmd, value };
    HAL_I2C_Master_Transmit(&hi2c1,  Adresa, buf, 2, 100);
}

void SHT_GetValue(uint8_t cmd, uint16_t *raw)
{
    uint8_t data[3];

    // pošalji komandu
    HAL_I2C_Master_Transmit(&hi2c1, Adresa, &cmd, 1, 100);


    if (cmd == TempRead) HAL_Delay(85);
    else HAL_Delay(30);


    HAL_I2C_Master_Receive(&hi2c1, Adresa, data, 3, 100);

    *raw = ((uint16_t)data[0] << 8) | data[1];
    *raw &= ~0x0003;
}

void SHT_GetTemp(float *temp)
{
    uint16_t raw = 0;
    SHT_GetValue(TempRead, &raw);

    *temp = -46.85f + (175.72f * ((float)raw / 65536.0f));
}

void SHT_GetHum(float *hum)
{
    uint16_t raw = 0;
    SHT_GetValue(HumRead, &raw);

    *hum = -6.0f + (125.0f * ((float)raw / 65536.0f));

    if (*hum > 100.0f) *hum = 100.0f;
    if (*hum < 0.0f) *hum = 0.0f;
}
