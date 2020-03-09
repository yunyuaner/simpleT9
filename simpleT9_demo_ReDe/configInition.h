/*******************************************************************************
 * 
 * 版权：             中国电子科技集团公司第三十二研究所
 * 描述：            本文件定义了运行ReWorks操作系统所需初始化接口，该文件被usrInit.c使用
 * 
 * 自动生成的文件。 不要进行编辑
 * 
 */


#ifndef REDE_CONFIGURATION_H_INCLUDED__
#define REDE_CONFIGURATION_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif


extern int sys_mem_init(u32 mm_type);
extern int symtbl_module_init(void);
#ifdef SHOW_ENABLE
#include <object_show.h>
#endif

#include <pthread_hook.h>
#include <pthread.h>

#ifdef SHOW_ENABLE
#include <pthread_show.h>
extern void pthread_show_init();
#endif

#include <mpart.h>

#ifdef SHOW_ENABLE
#include <mpart_show.h>
extern void mpart_show_init();
#endif

#include <memory.h>

#ifdef SHOW_ENABLE
#include <memory_show.h>
extern void mem_show_init();
#endif

#include <rtp.h>
#include <time.h>
#include <ratemon.h>
#include <wdg.h>

#ifdef SHOW_ENABLE
#include <timer_show.h>
extern void timer_show_init();
#include <ratemon_show.h>
extern void rms_show_init();
#include <wdg_show.h>
extern void wdg_show_init();
#endif

#include <semaphore.h>

#ifdef SHOW_ENABLE
#include <sem_show.h>
extern void sem_show_init();
#endif

#ifdef SHOW_ENABLE
#include <mutex_show.h>
extern void pthread_mutex_show_init();
#endif

#ifdef SHOW_ENABLE
#include <cond_show.h>
extern void cond_show_init();
#endif

#include <signal.h>

#ifdef SHOW_ENABLE
#include <signal_show.h>
extern void sig_show_init();
#endif

#include <mqueue.h>

#ifdef SHOW_ENABLE
#include <mqueue_show.h>
extern void mq_show_init();
#endif

#include <event.h>
extern void libc_module_init();
#include <reworks/monitor_cpu.h>

/* 针对所有任务的CPU使用率统计的模块，在所有新建任务之前初始化。 */
extern int thread_cpu_use_module_init();

#include <private/pgMgrLibP.h>
extern int mmu_module_init();
extern int rtp_module_extra_init();
extern int heap_mem_post_init();

extern int mmanLibInit();
extern int mmanFdLibInit();
extern void fpu_module_init();
extern int exception_module_init();
extern int exc_task_module_init();
extern void isr_nestable_set(u32 isr_flag, u32 fpu_flag);
extern int rtc_module_init(void);
#include <semLib.h>
#include <taskLib.h>
extern void udelay_module_init(void);
extern int cpu_up_sync(int);
#include <stdio.h>
extern int fsmgr_module_init(void);
extern int io_module_init(void);
extern int tty_module_init(void);
extern int buf_module_init(void);
extern int pty_module_init(int pty_num);
#include "netInit.h"

#ifdef IPNET_USE_DMA
#include <reworks/types.h>
extern PART_ID memNetPartId;
extern void mempart_to_dma(PART_ID *);
__DMA_MEMORY_PREASSIGNED(netbuf, IPNET_MEMORY_LIMIT << 20, 32);
#endif
extern int dosfs_module_init(int cache_size, int fd_mum);   
extern int shmFsLibInit(const char*);
extern int pci_config_init(int mechanism, unsigned long addr0, 
                       unsigned long addr1, unsigned long addr2);
extern int sys_pci_config_read(int bus,int dev,int func,int reg,int size,void *pResult);
extern int sys_pci_config_write(int bus,int dev,int func,int reg,int size,u32 data);
extern void sys_pci_auto_config();
#include <reworksio.h>
extern  void  serial_module_init();
extern int init_i2c();
extern void lm73_module_init();
#include <arpa/inet.h>
#include <ip/compat/ifLib.h>

extern void net_drv_init_gmac(void);
#include <arpa/inet.h>
#include <ip/compat/ifLib.h>

extern void net_drv_init_gmac(void);
extern int gpu_device_number;
extern int video_setup(char *mode,int bpp,char *name);
extern int usbInit(void);
extern int usrUsbHcdOhciAttach(void);
extern int usrUsbHcdEhciAttach(void);
#define INCLUDE_VXBUS
#define INCLUDE_VXB_CMDLINE
#define INCLUDE_HWMEM_ALLOC
#define INCLUDE_PARAM_SYS
#define INCLUDE_PLB_BUS
#define HWMEM_POOL_SIZE 100000

extern void vxbus_module_init();
#include <ip/compat/ifLib.h>
#include <arpa/inet.h>

#define INCLUDE_DMA_SYS
#define INCLUDE_MII_BUS
#define INCLUDE_GT64120A_PCI 
#define INCLUDE_PCI_BUS_AUTOCONF
#define INCLUDE_PCI_BUS_SHOW
#define INCLUDE_PCI_OLD_CONFIG_ROUTINES
#define INCLUDE_VXBUS_SHOW
#define INCLUDE_RTL8169_VXB_END
#define INCLUDE_GEI825XX_VXB_END 
#define INCLUDE_GENERICPHY
#define INCLUDE_BCM54XXPHY
#define INCLUDE_RTL8169PHY
#define DRV_INTCTLR_I8259
#define INCLUDE_PCI_BUS
#define INCLUDE_PCI 
#define INCLUDE_VXB_LEGACY_INTERRUPTS 

extern void vxbus_net_drv_init(void);
extern int if_addr6_add(char *interfaceName, char *interfaceAddress, int prefix_len, int flags);
extern int pci_module_init(void);
#ifndef INCLUDE_3A
extern int usb_bus_init(void);
#endif

#ifdef USB_USE_DMA
#include <reworks/types.h>
extern PART_ID memUSBPartId;
extern void mempart_to_dma(PART_ID *);
__DMA_MEMORY_PREASSIGNED(usb, 2<< 20, 32);
#endif
extern int telnet_module_init(void);
extern int ftp_module_init(void);
extern int shell_module_init(int);
extern void (*input_device_init_funcs[])(void);
extern void directfb_usbkeyboard_ctor ( void );
extern void directfb_usbkeyboard1_ctor ( void );
extern void directfb_usbkeyboard2_ctor ( void );
extern void (*interface_init_funcs[])(void);
extern void IDirectFBFont_FT2_ctor();
extern void (*interface_init_funcs[])(void);
extern void IDirectFBFont_DianZhen_ctor();
extern void (*input_device_init_funcs[])(void);
extern void directfb_vmouse_ctor ( void );
extern int vmse_module_init(void);
extern void (*input_device_init_funcs[])(void);
extern void directfb_keyboard_ctor ( void );
extern void (*input_device_init_funcs[])(void);
extern void directfb_ps2mouse_ctor ( void );
#include <vxbUsrCmdLine.c>

#ifdef CONFIGURE_INIT

void sysConfigInition()
{	
	/* 核心内存模块 */
	
	sys_mem_init(KERNEL_MM_METHOD);
	
	/* 符号表 */
	
	symtbl_module_init();
	
	/* 系统对象模块 */
	
	#ifdef SHOW_ENABLE
	object_show_init();
	#endif
	
	/* 任务钩子模块 */
	
	thread_hook_init();
	
	/* 核心任务模块 */
	
	thread_module_init(REWORKS_MAX_TASKS);
	#ifdef SHOW_ENABLE
	pthread_show_init();
	#endif
	
	
	/* 内存分区模块 */
	
	mpart_module_init(REWORKS_MAX_MPARTS);
	#ifdef SHOW_ENABLE
	mpart_show_init();
	#endif
	
	/* 用户堆模块 */
	
	#ifndef INCLUDE_MMU_CONFIG
	heap_mem_init(REWORKS_HEAP_ALGORITHM);
	#endif
	#ifdef SHOW_ENABLE
	mem_show_init();
	#endif
	
	
	/* 实时进程模块 */
	
	rtp_module_init(256);
	
	/* 定时器模块 */
	
	timer_module_init(REWORKS_MAX_TIMERS);
	rms_module_init(REWORKS_MAX_RMSES);
	wdg_module_init(REWORKS_MAX_WDGS);
	#ifdef SHOW_ENABLE
	timer_show_init();
	rms_show_init();
	wdg_show_init();
	#endif
	
	/* 信号量模块 */
	
	sem_module_init(REWORKS_MAX_SEMS);
	#ifdef SHOW_ENABLE
	sem_show_init();
	#endif
	
	/* 互斥量模块 */
	
	mutex_module_init(REWORKS_MAX_MUTEXES);
	#ifdef SHOW_ENABLE
	pthread_mutex_show_init();
	#endif
	
	/* 任务条件变量模块 */
	
	cond_module_init(REWORKS_MAX_CONDS);
	#ifdef SHOW_ENABLE
	cond_show_init();
	#endif
	
	/* 任务私有数据模块 */
	
	key_module_init(REWORKS_MAX_KEYS);
	
	/* 信号模块 */
	
	signal_module_init();
	#ifdef SHOW_ENABLE
	sig_show_init();
	#endif
	
	/* 消息队列模块 */
	
	mq_module_init(REWORKS_MAX_MSGQS);
	#ifdef SHOW_ENABLE
	mq_show_init();
	#endif
	
	/* 事件模块 */
	
	event_module_init();
	
	/* 任务C库支持模块 */
	
	libc_module_init();
	
	/* CPU使用监视模块 */
	
	/* 针对所有任务的CPU使用率统计的模块，在所有新建任务之前初始化。 */
	thread_cpu_use_module_init();
	
	
	/* MMU页式管理模式 */
	
	mmu_module_init();
	rtp_module_extra_init();
	heap_mem_post_init();
	
	pgMgrBaseLibInit();
	pgMgrLibInit();
	
	mmanLibInit();
	mmanFdLibInit();
	
	/* 浮点支持 */
	
	fpu_module_init();
	
	/* 异常处理模块 */
	
	exception_module_init();
	exc_task_module_init();
	
	/* 中断控制模块 */
	
	isr_nestable_set(ISR_NESTABLE, FPU_SAVECTX_ENABLE);
	
	/* 实时时钟 */
	
	rtc_module_init();
	
	/* VxWorks信号量模块 */
	
	semModuleInit();
	
	/* VxWorks任务模块 */
	
	taskLibInit();
	vx_fp_task_always_on(VX_FP_TASK_DEFAULT);

}


void userConfigInition()
{	
	/* 微秒级延时支持 */
	
	#if (!USE_TIME_BASE_REG)
	udelay_module_init();
	#endif
	
	/* CPU支持 */
	
	cpu_up_sync(CPU_NUMBER);
	
	
	
	/* 核间时钟同步 */
	
	extern void cores_time_sync();
	cores_time_sync();
	
	/* 基本模块 */
	
	fsmgr_module_init();
	#ifndef REWORKS_MIN_CONFIG
	typedef void(*PRINT_REWORKS_LOGO)(const char *fmt, ...);
	extern PRINT_REWORKS_LOGO reworks_logo_show_printx;
	reworks_logo_show_printx = (PRINT_REWORKS_LOGO)printf;
	#endif
	
	
	/* 扩展模块 */
	
	io_module_init();
	
	/* TTY模块 */
	
	tty_module_init();
	
	/* 缓冲模块 */
	
	buf_module_init();
	
	/* 伪终端 */
	
	pty_module_init(PTY_NUMBER);
	
	/* 增强型网络协议栈 */
	
	extern void net_module_init(unsigned int ipnet_memory_limit, int timeout_prio, int ipnet_to, int urgent_collection);
	extern int if_addr_set(char *interfaceName, char *interfaceAddress);
	extern int if_flag_change(char *interfaceName, int flags, int on);
	extern int ip_attach(int unit, char * pDevice);
	unsigned long inet_addr (const char *);
	extern int ifMaskSet (char *interfaceName, int netMask);
	
	#ifdef IPNET_USE_DMA
	mempart_to_dma(&memNetPartId);
	#endif
	
	net_module_init(IPNET_MEMORY_LIMIT, IPNET_TIMEOUT_JOB_PRIO, IPNET_REASSEMBLY_TIMEOUT, IPNET_URGENT_COLLECTION);
	
	
	/* DOS文件系统 */
	
	dosfs_module_init(DOSFS_CACHE_SIZE, DOSFS_MAX_FD_NUM);
	shmFsLibInit("/shm");
	
	/* PCI总线 */
	
	pci_config_init(PCI_MECHANISM, (int)sys_pci_config_read,(int)sys_pci_config_write,0);
	sys_pci_auto_config();
	
	/* 串口模块 */
	
	
	serial_module_init();
	
	
	/* I2C总线支持 */
	
	init_i2c();
	lm73_module_init();
	
	/* gmac1驱动配置 */
	
	net_drv_init_gmac();
	ipAttach(GMAC_NUMBER1,"gmac");				
	ifAddrSet( GMAC_HOST_NAME1, GMAC_IP_ADDRESS1);
	if_addr6_add( GMAC_HOST_NAME1, GMAC_IPv6_ADDRESS1, GMAC_IPv6_PRELEN1, GMAC_IPv6_FLAGS1);
	ifMaskSet(GMAC_HOST_NAME1, htonl(inet_addr(GMAC_SUBNETMASK1)));
	ifFlagChange( GMAC_HOST_NAME1, 1,TRUE);
	
	/* gmac0驱动配置 */
	
	net_drv_init_gmac();
	ipAttach(GMAC_NUMBER0,"gmac");				
	ifAddrSet( GMAC_HOST_NAME0, GMAC_IP_ADDRESS0);
	if_addr6_add( GMAC_HOST_NAME0, GMAC_IPv6_ADDRESS0, GMAC_IPv6_PRELEN0, GMAC_IPv6_FLAGS0);
	ifMaskSet(GMAC_HOST_NAME0, htonl(inet_addr(GMAC_SUBNETMASK0)));
	ifFlagChange( GMAC_HOST_NAME0, 1,TRUE);
	
	/* 图形系统配置 */
	
	if(GRAPHICS_GPU_DEVICE_OPEN == true)
	{	
	extern void (*gfxdriver_init_funcs)(void);// 输入设备函数指针数组
	extern void directfb_780E2d_ctor();
	gfxdriver_init_funcs = directfb_780E2d_ctor; 
	
	gpu_device_number = 3;
	}
	else
	gpu_device_number = 0;
	
	/* 显示驱动 */
	
	video_setup(FB_DEVICE_RESOLVE,FB_DEVICE_DEPTH,FB_DEVICE_NAME);
	ls2h_cursor_init(); 
	initbase();
	
	/* USB控制器 */
	
	usbInit();
	usrUsbHcdOhciAttach (); 
	usrUsbHcdEhciAttach (); 
	
	/* VXBUS 基本模块 */
	
	vxbus_module_init();
	
	/* VXBUS 网卡驱动 */
	
	vxbus_net_drv_init();
	
	/* PCI配置支持 */
	
	pci_module_init();
	
	/* USB总线支持 */
	
	#ifdef USB_USE_DMA
	mempart_to_dma(&memUSBPartId);
	#endif
	
	#ifndef INCLUDE_3A
	usb_bus_init();
	#endif
	
	
	/* TELNET服务 */
	
	telnet_module_init();
	
	/* FTP服务 */
	
	ftp_module_init();
	
	/* 人机交互外壳（shell） */
	
	#ifdef CONSOLE_OUTPUT_DEVICE_NAME
	shell_module_init(SHELL_PRIO);
	#endif
	
	/* USB键盘 */
	
	input_device_init_funcs[5] = directfb_usbkeyboard_ctor;
	input_device_init_funcs[6] = directfb_usbkeyboard1_ctor;
	input_device_init_funcs[7] = directfb_usbkeyboard2_ctor;
	
	/* TTF字体 */
	
	interface_init_funcs[0] = IDirectFBFont_FT2_ctor;
	
	/* 16号点阵字体 */
	
	interface_init_funcs[5] = IDirectFBFont_DianZhen_ctor;
	
	/* 虚拟鼠标 */
	
	input_device_init_funcs[3] = directfb_vmouse_ctor;
	vmse_module_init();
	
	/* PS2键盘 */
	
	input_device_init_funcs[1] = directfb_keyboard_ctor;
	
	/* PS2鼠标 */
	
	input_device_init_funcs[0] = directfb_ps2mouse_ctor;

}


#endif /* CONFIGURE_INIT */

#ifdef __cplusplus
}
#endif

#endif /* REDE_CONFIGURATION_H_INCLUDED__ */
