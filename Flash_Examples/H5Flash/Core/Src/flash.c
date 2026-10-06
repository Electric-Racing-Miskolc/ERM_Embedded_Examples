/*
 * flash.c
 *
 *  Created on: 2026. okt. 06.
 *      Author: csakm
 */
#include "main.h"
#include "flash.h"
#include "string.h"

uint32_t address = START_ADDRESS;

void Flash_Format_Storage(void){
	FLASH_EraseInitTypeDef erase_init;
	uint32_t sector_error = 0;

	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

	erase_init.TypeErase = FLASH_TYPEERASE_SECTORS;

	/*
	As the H5 uses a dual bank architecture that explains the "erase_init.Bank = FLASH_BANK_2"
	and it operates with 8Kb sectors, so 2048/4 = 256 to see how many pages there are total and that makes 128 sectors per bank
	and we erase the last 2 sectors hence the "erase_init.Sector = 126" and the "NbSectors = 2".
	*/
	//important to point to the 2nd Bank of the flash memory
	erase_init.Banks	 = FLASH_BANK_2;

	erase_init.Sector	 = FLASH_STORAGE_START_SECT;
	erase_init.NbSectors = FLASH_STORAGE_SECTOR_CNT;

	HAL_FLASHEx_Erase(&erase_init, &sector_error);
	HAL_FLASH_Lock();
}

void Flash_Write(void *data, uint32_t size_in_bytes){
	//The H5 series requires 16-byte alignment
	if(address % 16 != 0) return;

	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

	uint32_t current_address = address;
	uint8_t *data_ptr = (uint8_t*)data;
	uint32_t bytes_remaining = size_in_bytes;

	while(bytes_remaining > 0){
		//Create a 16-byte (128) blank canvas
		uint32_t chunk[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};

		//See if we have 16 bytes of data left, or less
		uint32_t bytes_to_copy = (bytes_remaining >= 16) ? 16 : bytes_remaining;

		memcpy(chunk, data_ptr, bytes_to_copy);

		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, current_address, (uint32_t)chunk) != HAL_OK){
			break; //Stop writing if the hardware rejects it
		}

		current_address += 16;
		data_ptr += bytes_to_copy;
		bytes_remaining -= bytes_to_copy;
	}
	address += ALIGN_16(size_in_bytes);
	HAL_FLASH_Lock();
}

void Flash_Read(uint32_t bookmark, void *destination, uint32_t size_in_bytes)
{
    memcpy(destination, (void *)bookmark, size_in_bytes);
}
