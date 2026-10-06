/*
 * flash.c
 *
 *  Created on: Oct 6, 2026
 *      Author: csakm
 */

#include "main.h"
#include "flash.h"
#include "string.h"

uint32_t address = START_ADDRESS;

void Flash_Erase(void)
{
	FLASH_EraseInitTypeDef erase_init;
	uint32_t page_error = 0;

    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);


    /*
	As the G4 uses a dual bank architecture that explains the "erase_init.Bank = FLASH_BANK_2"
	and it operates with 2Kb pages, so 512/2 = 256 to see how many pages there are total and that makes 128 pages per bank
	and we erase the last 2 pages hence the "erase_init.Page = 126" and the "NbPges = 2".
	*/
    //important to point to the 2nd Bank of the flash memory
    erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
    erase_init.Banks     = FLASH_BANK_2;
    erase_init.Page      = FLASH_STORAGE_START_PAGE; // 0x807F000 starts at Page 126
    erase_init.NbPages   = FLASH_STORAGE_PAGE_CNT;   // Erase Page 126 and 127

    HAL_FLASHEx_Erase(&erase_init, &page_error);
    // Reset trackers back to the start of the sector
    HAL_FLASH_Lock();
}

void Flash_Write(void *data, uint32_t size_in_bytes)
{
    if(address % 8 != 0) return; // Ensure 8-byte alignment

    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    uint32_t current_address = address;
    uint8_t *data_ptr = (uint8_t*)data;
    uint32_t bytes_remaining = size_in_bytes;

    while(bytes_remaining > 0)
    {
        // Create a blank 64-bit canvas (erased state is all 1s)
        uint64_t chunk = 0xFFFFFFFFFFFFFFFFULL;

        uint32_t bytes_to_copy = (bytes_remaining >= 8) ? 8 : bytes_remaining;

        // Copy up to 8 bytes of struct data into our 64-bit variable
        memcpy(&chunk, data_ptr, bytes_to_copy);

        // Write the 64-bit double-word to flash
        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, current_address, chunk) != HAL_OK)
        {
            break;
        }

        current_address += 8;
        data_ptr += bytes_to_copy;
        bytes_remaining -= bytes_to_copy;
    }

    // Push the global write tracker forward by the padded size
    address += ALIGN_8(size_in_bytes);

    HAL_FLASH_Lock();
}

void Flash_Read(uint32_t bookmark, void *destination, uint32_t size_in_bytes)
{
	//copy the data starting from the address given
    memcpy(destination, (void *)bookmark, size_in_bytes);
}
