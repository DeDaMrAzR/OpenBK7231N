/**
 * @file tuya_hal_storage.h
 * @brief STORAGE设备操作接口
 * 
 * @copyright Copyright(C),2018-2020, 涂鸦科技 www.tuya.com
 * 
 */

#ifndef __TUYA_HAL_STORAGE_H__
#define __TUYA_HAL_STORAGE_H__

#include "tuya_os_adapter.h"
#include <stdint.h>


#ifdef __cplusplus
	extern "C" {
#endif


/**
 * @brief read data from flash
 * 
 * @param[in]       addr        flash address
 * @param[out]      dst         pointer of buffer
 * @param[in]       size        size of buffer
 * @return int 0=成功，非0=失败
 */
int tuya_hal_flash_read(const unsigned int addr, unsigned char *dst, const unsigned int size);


/**
 * @brief write data to flash
 * 
 * @param[in]       addr        flash address
 * @param[in]       src         pointer of buffer
 * @param[in]       size        size of buffer
 * @return int 0=成功，非0=失败
 */
int tuya_hal_flash_write(const unsigned int addr, const unsigned char *src, const unsigned int size);


/**
 * @brief erase flash block
 * 
 * @param[in]       addr        flash block address
 * @param[in]       size        size of flash block
 * @return int 0=成功，非0=失败
 */
int tuya_hal_flash_erase(const unsigned int addr, const unsigned int size);


/**
 * @brief get description of storage
 * 
 * @return  pointer to storage description structure
 */
UNI_STORAGE_DESC_S* tuya_hal_storage_get_desc(void);


/**
 * @brief get UF file description
 * 
 * @return  pointer to descrtion of UF file
 */
UF_PARTITION_TABLE_S* tuya_hal_uf_get_desc(void);

/**
 * @brief get RCD file description
 * 
 * @return  pointer to descrtion of RCD file
 */
UF_PARTITION_TABLE_S *tuya_hal_rcd_get_desc();

/**
 * @brief get legacy swap description
 * 
 * @return  0-success, others-fail
 */
int tuya_hal_legacy_swap_get_desc(unsigned int *addr, unsigned int *size);


/**
 * @brief tuya_os_storage_intf_init用于初始化tuya storage组件接口
 * 
 * @return int 0=成功，非0=失败
 */

/* add begin: by sunkz, interface regist */
void tuya_os_storage_intf_init(void);
/* add end */



#ifdef __cplusplus
}
#endif

#endif // __TUYA_HAL_STORAGE_H__

