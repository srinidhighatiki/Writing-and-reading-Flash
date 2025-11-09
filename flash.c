#include "flash.h"
#include "stm32f4xx_hal.h"
#include "string.h"
#include "stdio.h"

static uint32_t GetSector(uint32_t Address)
{
    uint32_t sector = 0;

    if((Address < 0x08003FFF) && (Address >= 0x08000000))
    {
    sector = FLASH_SECTOR_0;
    }
    else if((Address < 0x08007FFF) && (Address >= 0x08004000))
    {
    sector = FLASH_SECTOR_1;
    }
    else if((Address < 0x0800BFFF) && (Address >= 0x08008000))
    {
    sector = FLASH_SECTOR_2;
    }
    else if((Address < 0x0800FFFF) && (Address >= 0x0800C000))
    {
    sector = FLASH_SECTOR_3;
    }
    else if((Address < 0x0801FFFF) && (Address >= 0x08010000))
    {
    sector = FLASH_SECTOR_4;
    }
    else if((Address < 0x0803FFFF) && (Address >= 0x08020000))
    {
    sector = FLASH_SECTOR_5;
    }
    else if((Address < 0x0805FFFF) && (Address >= 0x08040000))
    {
    sector = FLASH_SECTOR_6;
    }
    else if((Address < 0x0807FFFF) && (Address >= 0x08060000))
    {
    sector = FLASH_SECTOR_7;
    }
    return sector;
}

// uint8_t bytes_tem[4];

// void float2Bytes(uint8_t * ftoa_bytes_temp,float float_variable)
// {
//     union 
//     {
//         float a;
//         uint8_t bytes[4];
//     };thing
    
// }

uint32_t Flash_Write_Data (uint32_t StartSectorAddress, uint32_t *Data, uint16_t numberofwords)
{
    static FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t SECTORError;
    int sofar = 0;
    /*Unlock flash*/
    HAL_FLASH_Unlock();

    /*Erase flash area*/

    uint32_t StartSector = GetSector(StartSectorAddress);
    uint32_t EndSectorAddress = StartSectorAddress + numberofwords*4;
    uint32_t EndSector = GetSector(EndSectorAddress);
    
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector = StartSector;
    EraseInitStruct.NbSectors = (EndSector - StartSector) + 1;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
    {
        return HAL_FLASH_GetError();
    }

    while (sofar<numberofwords)
    {
        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartSectorAddress, Data[sofar]) == HAL_OK)
        {
            StartSectorAddress += 4;
            sofar++;
        }
        else{
            return HAL_FLASH_GetError();
        }
    }

    /*Lock flash*/
    HAL_FLASH_Lock();

    return 0;

}

void Flash_Read_Data (uint32_t StartSectorAddress, uint32_t *RxBuf, uint16_t numberofwords)
{
    while(1)
    {
        *RxBuf = *(__IO uint32_t *)StartSectorAddress;
        StartSectorAddress += 4;
        RxBuf++;
        if (!(numberofwords--)) break; 
    }
}

void Convert_To_Str (uint32_t *Data, char *Buf)
{
    int numberofbytes = ((strlen((char *)Data)/4) + ((strlen((char *)Data)%4)!=0)) *4;
    for (int i = 0; i<numberofbytes; i++)
    {
        Buf[i] = Data[i/4]>>(8*(i%4));
    }
}
