/*
 * sht.h
 *
 *  Created on: Feb 20, 2026
 *      Author: Ivan Hodak
 */

#ifndef INC_SHT_H_
#define INC_SHT_H_

#include "main.h"

#define SoftReset 0xFE
#define TempRead  0xF3
#define HumRead   0xF5
#define WriteCmd  0xE6
#define ReadCmd   0xE7
#define Adresa (0x40 << 1)

// -------------------------
//  Deklaracije funkcija
// -------------------------

void SHT_Init();

void SHT_ReadReg(uint8_t *value);

void SHT_WriteReg(uint8_t value);

void SHT_GetValue(uint8_t cmd, uint16_t *raw);

void SHT_GetTemp(float *temp);

void SHT_GetHum(float *hum);

#endif /* INC_SHT_H_ */
