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

#include "../../platforms.h"



#include "../../../inc/MarlinConfig.h"

#if HAS_SPI_TFT

#include "tft_spi.h"
   uint8_t TFT_SPI::data_type;

void TFT_SPI::Init() {
      data_type=DATASIZE_16BIT;
}

void TFT_SPI::DataTransferBegin(uint16_t DataSize) {
     data_type=DataSize&0xff;
}

#ifdef TFT_DEFAULT_DRIVER
  #include "../../../lcd/tft_io/tft_ids.h"
#endif

uint32_t TFT_SPI::GetID() {
//  uint32_t id;
//  id = ReadID(LCD_READ_ID);
//  if ((id & 0xFFFF) == 0 || (id & 0xFFFF) == 0xFFFF) {
//    id = ReadID(LCD_READ_ID4);
//    #ifdef TFT_DEFAULT_DRIVER
//      if ((id & 0xFFFF) == 0 || (id & 0xFFFF) == 0xFFFF)
//        id = TFT_DEFAULT_DRIVER;
//    #endif
//   }
//  return id;
  return 0;
}

uint32_t TFT_SPI::ReadID(uint16_t Reg) {
//  uint32_t Data = 0;
//  #if PIN_EXISTS(TFT_MISO)
//    uint32_t BaudRatePrescaler = SPIx.Init.BaudRatePrescaler;
//    uint32_t i;

//    SPIx.Init.BaudRatePrescaler = SPIx.Instance == SPI1 ? SPI_BAUDRATEPRESCALER_8 : SPI_BAUDRATEPRESCALER_4;
//    DataTransferBegin(DATASIZE_8BIT);
//    WriteReg(Reg);

//    if (SPIx.Init.Direction == SPI_DIRECTION_1LINE) SPI_1LINE_RX(&SPIx);
//    __HAL_SPI_ENABLE(&SPIx);

//    for (i = 0; i < 4; i++) {
//      #if TFT_MISO_PIN != TFT_MOSI_PIN
//        //if (hspi->Init.Direction == SPI_DIRECTION_2LINES) {
//          while ((SPIx.Instance->SR & SPI_FLAG_TXE) != SPI_FLAG_TXE) {}
//          SPIx.Instance->DR = 0;
//        //}
//      #endif
//      while ((SPIx.Instance->SR & SPI_FLAG_RXNE) != SPI_FLAG_RXNE) {}
//      Data = (Data << 8) | SPIx.Instance->DR;
//    }

//    __HAL_SPI_DISABLE(&SPIx);
//    DataTransferEnd();

//    SPIx.Init.BaudRatePrescaler   = BaudRatePrescaler;
//  #endif

//  return Data >> 7;
    return 0;
}

bool TFT_SPI::isBusy() {


//    volatile bool dmaEnabled = (DMAtx.Instance->CCR & DMA_CCR_EN) != RESET;

//  if (dmaEnabled) {
//    if (__HAL_DMA_GET_FLAG(&DMAtx, __HAL_DMA_GET_TC_FLAG_INDEX(&DMAtx)) != 0 || __HAL_DMA_GET_FLAG(&DMAtx, __HAL_DMA_GET_TE_FLAG_INDEX(&DMAtx)) != 0)
//      Abort();
//  }
//  else
//    Abort();
//  return dmaEnabled;
  return 0;
}

void TFT_SPI::Abort() {
//  // Wait for any running spi
//  while ((SPIx.Instance->SR & SPI_FLAG_TXE) != SPI_FLAG_TXE) {}
//  while ((SPIx.Instance->SR & SPI_FLAG_BSY) == SPI_FLAG_BSY) {}
//  // First, abort any running dma
//  HAL_DMA_Abort(&DMAtx);
//  // DeInit objects
//  HAL_DMA_DeInit(&DMAtx);
//  HAL_SPI_DeInit(&SPIx);
//  // Deselect CS
//  DataTransferEnd();
}

void TFT_SPI::Transmit(uint16_t Data) {
     if( data_type==DATASIZE_16BIT)
     {
       LCD_WR_DATA(Data); 
     }
     else
     {
       LCD_WR_DATA8(Data&0xff);
     }
//  if (TFT_MISO_PIN == TFT_MOSI_PIN)
//    SPI_1LINE_TX(&SPIx);

//  __HAL_SPI_ENABLE(&SPIx);

//  SPIx.Instance->DR = Data;

//  while ((SPIx.Instance->SR & SPI_FLAG_TXE) != SPI_FLAG_TXE) {}
//  while ((SPIx.Instance->SR & SPI_FLAG_BSY) == SPI_FLAG_BSY) {}

//  if (TFT_MISO_PIN != TFT_MOSI_PIN)
//    __HAL_SPI_CLEAR_OVRFLAG(&SPIx);   // Clear overrun flag in 2 Lines communication mode because received is not read
}

void TFT_SPI::TransmitDMA(uint32_t MemoryIncrease, uint16_t *Data, uint16_t Count) {
  // Wait last dma finish, to start another
//  while (isBusy()) { /* nada */ }

//  DMAtx.Init.MemInc = MemoryIncrease;
//  HAL_DMA_Init(&DMAtx);

//  if (TFT_MISO_PIN == TFT_MOSI_PIN)
//    SPI_1LINE_TX(&SPIx);

//  DataTransferBegin();

//  HAL_DMA_Start(&DMAtx, (uint32_t)Data, (uint32_t)&(SPIx.Instance->DR), Count);
//  __HAL_SPI_ENABLE(&SPIx);

//  SET_BIT(SPIx.Instance->CR2, SPI_CR2_TXDMAEN);   // Enable Tx DMA Request

//  HAL_DMA_PollForTransfer(&DMAtx, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
//  Abort();
}

#endif // HAS_SPI_TFT

