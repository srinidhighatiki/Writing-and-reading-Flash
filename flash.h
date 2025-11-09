#ifndef INC_FLASH_H_
#define INC_FLASH_H_   

#include "stdint.h"

uint32_t Flash_Write_Data(uint32_t StartSectorAddress, uint32_t *Data, uint16_t numberofwords);

void Flash_Read_Data(uint32_t StartAddress, uint32_t *RxBuf, uint16_t numberofwords);

void Convert_To_Str(uint32_t *Data, char *Buf);

#endif /*INC_FLASH_H_*/