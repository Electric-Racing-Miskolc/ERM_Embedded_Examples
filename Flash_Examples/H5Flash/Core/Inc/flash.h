/*
 * flash.h
 *
 *  Created on: Oct 6, 2026
 *      Author: csakm
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#define FLASH_STORAGE_START_SECT  126  // Sector 126 of Bank 2
#define FLASH_STORAGE_SECTOR_CNT  2    // Erases Sectors 126 and 127

#define ALIGN_16(size)            (((size) + 15) & ~15)

#define START_ADDRESS 0x081fc000

void Flash_Format_Storage(void);
void Flash_Write(void *data, uint32_t size_in_bytes);
void Flash_Read(uint32_t bookmark, void *destination, uint32_t size_in_bytes);

#endif /* INC_FLASH_H_ */
