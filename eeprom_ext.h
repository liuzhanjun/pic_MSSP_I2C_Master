/* 
 * File:   eeprom_ext.h
 * Author: YH31
 *
 * Created on May 15, 2020, 10:56 AM
 */

#ifndef EEPROM_EXT_H
#define	EEPROM_EXT_H
#include "I2C.h"

#include <stdint.h>


char eeprom_wb(int16_t addr, int8_t data);
char eeprom_rb(int16_t addr);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_EXT_H */

