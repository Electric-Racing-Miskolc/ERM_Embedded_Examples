/*
 * flash.h
 *
 *  Created on: Oct 6, 2026
 *      Author: csakm
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#define ALIGN_8(size)         (((size) + 7) & ~7)
#define START_ADDRESS   0x807F000
#define FLASH_STORAGE_START_PAGE  126  // Sector 126 of Bank 2
#define FLASH_STORAGE_PAGE_CNT  2    // Erases Sectors 126 and 127

void Flash_Erase(void);
void Flash_Write(void *data, uint32_t size_in_bytes);
void Flash_Read(uint32_t bookmark, void *destination, uint32_t size_in_bytes);

#endif /* INC_FLASH_H_ */
