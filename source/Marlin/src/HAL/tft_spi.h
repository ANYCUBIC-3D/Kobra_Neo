/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once
#include "bsp_spi_tft.h"
#include "stdint.h"
#ifndef LCD_READ_ID
  #define LCD_READ_ID 0x04   // Read display identification information (0xD3 on ILI9341)
#endif
#ifndef LCD_READ_ID4
  #define LCD_READ_ID4 0xD3   // Read display identification information (0xD3 on ILI9341)
#endif

#define DATASIZE_8BIT    0//SPI_DATASIZE_8BIT
#define DATASIZE_16BIT   1//SPI_DATASIZE_16BIT
#define TFT_IO_DRIVER TFT_SPI

class TFT_SPI {
private:
//  static SPI_HandleTypeDef SPIx;
//  static DMA_HandleTypeDef DMAtx;
  static uint8_t data_type;
  static uint32_t ReadID(uint16_t Reg);
  static void Transmit(uint16_t Data);
  static void TransmitDMA(uint32_t MemoryIncrease, uint16_t *Data, uint16_t Count);

public:
  static void Init();
  static uint32_t GetID();
  static bool isBusy();
  static void Abort();

  static void DataTransferBegin(uint16_t DataWidth);
  static void DataTransferEnd() { }//WRITE(TFT_CS_PIN, HIGH); };
  static void DataTransferAbort();

  static void WriteData(uint16_t Data) {
    if(data_type==DATASIZE_16BIT)
    LCD_WR_DATA(Data);
    else
    LCD_WR_DATA8(Data&0xff);
    }//Transmit(Data); }
  static void WriteReg(uint16_t Reg)   { LCD_WR_REG(Reg&0xff);}//WRITE(TFT_A0_PIN, LOW); Transmit(Reg); WRITE(TFT_A0_PIN, HIGH); }

  static void WriteSequence(uint16_t *Data, uint16_t Count) {
    uint16_t i;
    for(i=0;i<Count;i++)
    {
      LCD_WR_DATA(Data[i]);
    }
    }// TransmitDMA(DMA_MINC_ENABLE, Data, Count); }

  static void WriteMultiple(uint16_t Color, uint32_t Count) {
        uint16_t i;
    for(i=0;i<Count;i++)
    {
      LCD_WR_DATA(Color);
    }
  }
    /*
    static uint16_t Data; Data = Color;
    while (Count > 0) {
      TransmitDMA(DMA_MINC_DISABLE, &Data, Count > 0xFFFF ? 0xFFFF : Count);
      Count = Count > 0xFFFF ? Count - 0xFFFF : 0;
    }
  }
    */
};
