/*
 * 
 * kbd_ch423.h
 * 
 * 
 * ch423键盘接口
 * 
 * 
 * 2019-10-26:dengpan create
 * */


#ifndef	__KBD_CH423_H__
#define	__KBD_CH423_H__

#ifdef	__cplusplus
extern "C"{
#endif 

#include <reworks/types.h>
//#include <driver.h>
//#include <buf.h>
//#include <keycode.h>

/* CH452 reg */
#define		CH452_I2C_ADDR0				0x20			
#define		CH452_I2C_ADDR1				0x30			
#define		CH452_I2C_MASK				0x3E			

#define     CH452_I2C_ADDR      		CH452_I2C_ADDR0

#define     REG_SET_SYS_PARAM           0x04   
#define     REG_SET_DISPLAY_PARAM       0x05  
#define     REG_READ_CHIP_VER           0x00    
#define     REG_READ_KEYBOARD_CODE      0x07    
#define     REG_RESET_CHIP              0x02

#define     ADDR_SET_SYS_PARAM           (CH452_I2C_ADDR | REG_SET_SYS_PARAM)
#define     ADDR_SET_DISPLAY_PARAM       (CH452_I2C_ADDR | REG_SET_DISPLAY_PARAM)
#define     ADDR_READ_CHIP_VER           (CH452_I2C_ADDR | REG_READ_CHIP_VER)
#define     ADDR_READ_KEYBOARD_CODE      (CH452_I2C_ADDR | REG_READ_KEYBOARD_CODE)
#define     ADDR_RESET_CHIP              (CH452_I2C_ADDR | REG_RESET_CHIP)

//int initKbdCh423(struct kbd_device_struct *kbd);

#ifdef	__cplusplus
}
#endif 


#endif	/*__KBD_CH423_H__*/
