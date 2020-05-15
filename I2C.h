/* 
 * File:   I2C.h
 * Author: YH31
 *
 * Created on May 13, 2020, 2:09 PM
 */

#ifndef I2C_H
#define	I2C_H
#include <xc.h>
#include <stdint.h>
#define SCL PORTCbits.RC3
#define SDA PORTCbits.RC4
void delay();
void i2c_init();
void i2c_start();


char i2c_write(uint8_t data);
char i2c_read(char ack);
void i2c_stop();
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

