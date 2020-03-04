/*
 * 
 * kbd_ch423.c
 * 
 * 
 * ch423键盘接口
 * 
 * 
 * 2019-10-26:dengpan create
 * */
#include <semaphore.h>
#include <pthread.h>
#include <clock.h>
#include <irq.h>
#include <atomic.h>
//#include "gpio.h"
#include "key_codes.h"
#include "kbd_ch423.h"

typedef void(*wdgFunc)(void *arg);

/*MACRO*/
#if 0
#define KEY_A			30
#define KEY_S			31
#define KEY_D			32
#define KEY_F			33
#define KEY_G			34
#define KEY_H			35
#define KEY_J			36
#define KEY_K			37
#define KEY_L			38
#define KEY_Q			16
#define KEY_W			17
#define KEY_E			18
#define KEY_R			19
#define KEY_T			20
#define KEY_Y			21
#define KEY_U			22
#define KEY_I			23
#define KEY_O			24
#define KEY_P			25
#define KEY_Z			44
#define KEY_X			45
#define KEY_C			46
#define KEY_V			47
#define KEY_B			48
#define KEY_N			49
#define KEY_M			50
#endif

/*LOCAL*/
static int KbdCh423Read(u8 offset, u8* pVal);
extern int KbdCh423Write(u8 offset, u8 val);
static void* KbdCh423Hander(void* param);
static void OnRxKbdCh423(struct kbd_device_struct* pKbd);
static u8 OnRxKbdContinue(struct kbd_device_struct* pKbd,u8 code, int continueTimes);
static int KbdCh423Setup();
static sem_t sg_semSync = 0;
static pthread_t sg_threadRx = 0;
static u64	sg_lastTick = 0;
static u8   sg_lastCode = 0;
static int	sg_continueTimes = 0;

static int caps_lock = 0;

static const unsigned char sg_keymap[92] = {
		[KEY_F1_CH423] = KEY_F1,	//F1
		[KEY_F2_CH423] = KEY_F2,	//F2
		[KEY_F3_CH423] = KEY_F3,	//F3
		[KEY_F4_CH423] = KEY_F4,	//F4
		[KEY_F5_CH423] = KEY_F5,	//F5
		[5] = 0,
		[6] = 0,
		[7] = 0,

		[KEY_F6_CH423] = KEY_F6,	//F6
		[KEY_F7_CH423] = KEY_F7,	//F7
		// [9] = 3,	//2
		[KEY_F8_CH423] = KEY_F8,	//F8
		[KEY_F9_CH423] = KEY_F9,	//F9
		[KEY_F10_CH423] = KEY_F10,	//F10
		[13] = 0,
		[14] = 0,
		[15] = 0,

		[16] = 103,	//F11 KEY_UP
		[KEY_PAGEUP_CH423] = KEY_PAGEUP,	//KEY_PAGEUP
		[18] = KEY_1,	//1
		[19] = KEY_2,	//2
		[20] = KEY_3,	//3
		[21] = KEY_4,	//4
		[22] = KEY_5,	//5
		[23] = 0,

		[KEY_DOWN_CH423] = KEY_DOWN,	//F12 KEY_DOWN
		[KEY_PAGEDOWN_CH423] = KEY_PAGEDOWN,	//KEY_PAGEDOWN
		[26] = KEY_6,	//6
		[27] = KEY_7,	//7
		[28] = KEY_8,	//8
		[29] = KEY_9,	//9
		[30] = KEY_0,	//0
		[31] = 0,

		[KEY_DOT_CH423] = KEY_DOT,	//KEY_DOT
		[KEY_UP_CH423] = KEY_UP,	//KEY_UP
		[KEY_MINUS_CH423] = KEY_MINUS,	//KEY_MINUS
		[KEY_BACKSPACE_CH423] = KEY_BACKSPACE,	//KEY_DELETE---KEY_BACKSPACE
		[KEY_ESC_CH423] = KEY_ESC,	//KEY_ESC
		[37] = 0,
		[38] = 0,
		[39] = 0,

		[KEY_LEFT_CH423] = KEY_LEFT,	//KEY_LEFT
		[KEY_DOWN_CH423] = KEY_DOWN,	//KEY_DOWN
		[KEY_RIGHT_CH423] = KEY_RIGHT,	//KEY_RIGHT
		[KEY_SPACE_CH423] = KEY_SPACE,	//KEY_SPACE
		[KEY_ENTER_CH423] = KEY_ENTER,	//KEY_ENTER
		[45] = 0,
		[46] = 0,
		[47] = 0,

		[KEY_A_CH423] = KEY_A,
		[KEY_B_CH423] = KEY_B,
		[KEY_C_CH423] = KEY_C,
		[51] = 0,
		[KEY_D_CH423] = KEY_D,
		[KEY_E_CH423] = KEY_E,
		[KEY_F_CH423] = KEY_F,
		[55] = 0,

		[KEY_G_CH423] = KEY_G,
		[KEY_H_CH423] = KEY_H,
		[KEY_I_CH423] = KEY_I,
		[59] = 0,
		[KEY_J_CH423] = KEY_J,
		[KEY_K_CH423] = KEY_K,
		[KEY_L_CH423] = KEY_L,
		[63] = 0,

		[KEY_M_CH423] = KEY_M,
		[KEY_N_CH423] = KEY_N,
		[KEY_O_CH423] = KEY_O,
		[67] = 0,
		[68] = 0,
		[69] = 0,
		[70] = 0,
		[71] = 0,

		[72] = 0,
		[73] = 0,
		[74] = 0,
		[75] = 0,
		[76] = 0,
		[77] = 0,
		[78] = 0,
		[79] = 0,

		[KEY_P_CH423] = KEY_P,
		[KEY_Q_CH423] = KEY_Q,
		[KEY_R_CH423] = KEY_R,
		[KEY_S_CH423] = KEY_S,
		[KEY_T_CH423] = KEY_T,
		[KEY_U_CH423] = KEY_U,
		[KEY_V_CH423] = KEY_V,
		[87] = 0,

		[KEY_W_CH423] = KEY_W,
		[KEY_X_CH423] = KEY_X,
		[KEY_Y_CH423] = KEY_Y,
		[KEY_Z_CH423] = KEY_Z,
};

/*EXPORT*/
//extern int registerI2c();
//extern int readFromI2cEx(int no, int addr, u8* pBuf, int len);
//extern int writeToI2cEx(int no, int addr, u8 const* pBuf, int len);
//extern int printk(const char *fmt, ...);
/*MACRO*/
#define	KBD_CH423_I2C_CTL_NO			1
#define KBD_CH423_I2C_DEV_ADDR			0x24
#define	KBD_CH423_IRQ_NO				59
#define	KBD_CH423_GPIO_NO				6
#define	KBD_CH423_KEYS_MAX				sizeof(sg_keymap)/sizeof(sg_keymap[0])

int KbdCh423Read(u8 addr, u8* pVal)
{
	return readFromI2cEx(KBD_CH423_I2C_CTL_NO, addr, pVal, 1);
}

int KbdCh423Write(u8 addr, u8 val)
{
	return writeToI2cEx(KBD_CH423_I2C_CTL_NO, addr, &val, 1);
}

u8 OnRxKbdContinue(struct kbd_device_struct* pKbd,u8 key, int continueTimes)
{
	int offset;
	int index;

    switch (key) {
        case KEY_2_CH423:
        case KEY_3_CH423:
        case KEY_4_CH423:
        case KEY_5_CH423:
            offset = continueTimes&0x3;
            if (offset) {
                index = (KEY_A_CH423 - 1) + (key - KEY_2_CH423) * 4;
                key = index + offset;
            }
            break;

        case KEY_6_CH423:
            offset = continueTimes;
            if (offset) {
                index = (KEY_M_CH423 - 1);
                key = index + offset;
            }
            break;

        case KEY_7_CH423:
            offset = continueTimes;
            if (offset) {
                index = (KEY_P_CH423 - 1);
                key = index + offset;
            }
            break;

        case KEY_8_CH423:
            offset = continueTimes;
            if (offset) {
                index = (KEY_T_CH423 - 1);
                key = index + offset;
            }
            break;

        case KEY_9_CH423:
            offset = continueTimes;
            if (offset) {
                index = (KEY_W_CH423 - 1);
                key = index + offset;
            }
            break;

        case KEY_F10_CH423:
            caps_lock = !caps_lock;
        case KEY_1_CH423:
        default:
            return key;
            break;
    };    		

    /* 'Backspace' Key_Down + Key_Up */
	keycode_handler(pKbd, 0x0e);
	keycode_handler(pKbd, 0x0e|0x80);

    return key;
}


void OnRxKbdCh423(struct kbd_device_struct* pKbd)
{
	// linux 驱动是中断发生后30毫秒读键盘
	u8 code;
	int ret = KbdCh423Read(ADDR_READ_KEYBOARD_CODE, &code);
	if (ret < 0)
		return;
	//printk("KbdCh423Read Code 0x%x\n",code);
	
	u64 curTick = tick_get();
	
	u8 checkTimes = curTick - sg_lastTick;
	if ((checkTimes < 10) && (code == sg_lastCode))
		return;
	
	u8 key = code& 0x3f;
	if (key >= KBD_CH423_KEYS_MAX)
		return;
	

	if ((checkTimes > 10) && (checkTimes < 60) && (code == sg_lastCode))
	{
		key = OnRxKbdContinue(pKbd,key, ++sg_continueTimes);
	}
	else
	{
		sg_continueTimes = 0;
	}

	sg_lastTick = curTick;
	sg_lastCode = code;

	
	if (sg_keymap[key] != 0)
	{
	    if (!caps_lock)
        {   
    		keycode_handler(pKbd, sg_keymap[key]);
    		keycode_handler(pKbd, sg_keymap[key]|0x80);
        }
        else
        {
            keycode_handler(pKbd, KEY_LEFTSHIFT);    		
            keycode_handler(pKbd, sg_keymap[key]);
            keycode_handler(pKbd, sg_keymap[key]|0x80);
    		keycode_handler(pKbd, KEY_LEFTSHIFT|0x80);
        }
	}
}

void* KbdCh423Hander(void* param)
{
	sem_post(&sg_semSync); 
	return 0;
}

void* KdbCh423Work(void* param)
{
	struct kbd_device_struct* kbd = (struct kbd_device_struct* )param;
	
	while (1)
	{
		int ret = sem_wait2(&sg_semSync, WAIT, 100);
		if (ret == 0)
		{
			OnRxKbdCh423(kbd);
		}
		else
		{
		}

	}
}

int KbdCh423Setup()
{
	int ret;
	u8 val;
	int trytimes =5;
_RETRY:
	ret = KbdCh423Write(0x27, 0x01);
	if ((ret < 0)&&(trytimes-- > 0))
	{
		usleep(100000);
		goto _RETRY;
	}
	
	if (ret < 0)
	{
		printk("ch423 error*****************\n");
		return -1;
	}
	
	ret = KbdCh423Read(ADDR_READ_CHIP_VER, &val);
	if (ret < 0)
		return -1;
	printk("KBD CH423 VER 0x%x\n", val);

	ret = KbdCh423Write(ADDR_SET_SYS_PARAM, 0x22);
	if (ret < 0)
		return -1;
	
	ret = KbdCh423Read(ADDR_SET_SYS_PARAM, &val);
	if (ret < 0)
		return -1;
	
	printk("KBD CH423 SYS PARAM SET 0x%x\n", val);
	
	ret = KbdCh423Read(ADDR_READ_KEYBOARD_CODE, &val);
	
	printk("KBD CH423 read Code 0x%x\n", val);
	return ret;
}

void readKbdCh423(u8 offset)
{
	u8 val = 0;
	KbdCh423Read(offset, &val);
	printf("val 0x%x\n", val);
}
int initKbdCh423(struct kbd_device_struct *kbd)
{
	if (sg_threadRx != 0)
		return 0;
	
	//gpio 初始化
	u32 muxCtl = 0xb0010440;
	u32 muxVal = *(volatile u32* )muxCtl;
	muxVal &=~(1<< 2) ;
	 *(volatile u32* )muxCtl = muxVal;
	 

	//gpioDirectSet(KBD_CH423_GPIO_NO, GPIO_DIRECTION_IN);
	
	int ret = registerI2c();		// 初始化I2C驱动
	if (ret < 0)
	{
		printk("i2c init fail\n");
		return -1;
	}

	// ch423 初始化
	ret = KbdCh423Setup();
	if (ret < 0)
	{
		printk("KbdCh423Setup fail\n");
		return -1;
	}
	
	ret = sem_init2(&sg_semSync, 0, SEM_BINARY, PTHREAD_WAITQ_FIFO, 0);
	if (ret < 0)
		return -1;
	
	ret = pthread_create2(&sg_threadRx, "tRxCh423", 155, 0, 1024*20, KdbCh423Work, kbd);
	if (ret < 0)
		goto _ERROR_THREAD;
	
	ret = shared_int_install(KBD_CH423_IRQ_NO, (INT_HANDLER)KbdCh423Hander, kbd);
	if (ret < 0)
		goto _ERROR;
	
	gpioIrqEnable(KBD_CH423_GPIO_NO);
	int_enable_pic(KBD_CH423_IRQ_NO);
	kbd->kbd_hw_led_set = NULL;
	return 0;
_ERROR:
	pthread_cancel(sg_threadRx);
	sg_threadRx = 0;
	
_ERROR_THREAD:
	sem_destroy(&sg_semSync);
	sg_threadRx =0;
	return -1;
}
