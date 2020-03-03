/*******************************************************************************
 * 
 * ��Ȩ��             �й����ӿƼ����Ź�˾����ʮ���о���
 * ������            ���ļ�����������ReWorks����ϵͳ�����ʼ���ӿڣ����ļ���usrInit.cʹ��
 * 
 * �Զ����ɵ��ļ��� ��Ҫ���б༭
 * 
 */


#ifndef REDE_CONFIGURATION_H_INCLUDED__
#define REDE_CONFIGURATION_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif


extern int sys_mem_init(u32 mm_type);
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

#include <mqueue.h>

#ifdef SHOW_ENABLE
#include <mqueue_show.h>
extern void mq_show_init();
#endif

#include <event.h>
extern void libc_module_init();
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
#include <taskLib.h>
extern void udelay_module_init(void);
extern int cpu_up_sync(int);
#include <stdio.h>
extern int fsmgr_module_init(void);
extern int io_module_init(void);
extern int tty_module_init(void);
extern int buf_module_init(void);
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
extern int gpu_device_number;
extern int video_setup(char *mode,int bpp,char *name);
extern int pci_module_init(void);

#ifdef CONFIGURE_INIT

void sysConfigInition()
{	
	/* �����ڴ�ģ�� */
	
	sys_mem_init(KERNEL_MM_METHOD);
	
	/* ϵͳ����ģ�� */
	
	#ifdef SHOW_ENABLE
	object_show_init();
	#endif
	
	/* ������ģ�� */
	
	thread_hook_init();
	
	/* ��������ģ�� */
	
	thread_module_init(REWORKS_MAX_TASKS);
	#ifdef SHOW_ENABLE
	pthread_show_init();
	#endif
	
	
	/* �ڴ����ģ�� */
	
	mpart_module_init(REWORKS_MAX_MPARTS);
	#ifdef SHOW_ENABLE
	mpart_show_init();
	#endif
	
	/* �û���ģ�� */
	
	#ifndef INCLUDE_MMU_CONFIG
	heap_mem_init(REWORKS_HEAP_ALGORITHM);
	#endif
	#ifdef SHOW_ENABLE
	mem_show_init();
	#endif
	
	
	/* ʵʱ����ģ�� */
	
	rtp_module_init(256);
	
	/* �ź���ģ�� */
	
	sem_module_init(REWORKS_MAX_SEMS);
	#ifdef SHOW_ENABLE
	sem_show_init();
	#endif
	
	/* ������ģ�� */
	
	mutex_module_init(REWORKS_MAX_MUTEXES);
	#ifdef SHOW_ENABLE
	pthread_mutex_show_init();
	#endif
	
	/* ������������ģ�� */
	
	cond_module_init(REWORKS_MAX_CONDS);
	#ifdef SHOW_ENABLE
	cond_show_init();
	#endif
	
	/* ����˽������ģ�� */
	
	key_module_init(REWORKS_MAX_KEYS);
	
	/* ��Ϣ����ģ�� */
	
	mq_module_init(REWORKS_MAX_MSGQS);
	#ifdef SHOW_ENABLE
	mq_show_init();
	#endif
	
	/* �¼�ģ�� */
	
	event_module_init();
	
	/* ����C��֧��ģ�� */
	
	libc_module_init();
	
	/* MMUҳʽ����ģʽ */
	
	mmu_module_init();
	rtp_module_extra_init();
	heap_mem_post_init();
	
	pgMgrBaseLibInit();
	pgMgrLibInit();
	
	mmanLibInit();
	mmanFdLibInit();
	
	/* ����֧�� */
	
	fpu_module_init();
	
	/* �쳣����ģ�� */
	
	exception_module_init();
	exc_task_module_init();
	
	/* �жϿ���ģ�� */
	
	isr_nestable_set(ISR_NESTABLE, FPU_SAVECTX_ENABLE);
	
	/* ʵʱʱ�� */
	
	rtc_module_init();
	
	/* VxWorks����ģ�� */
	
	taskLibInit();
	vx_fp_task_always_on(VX_FP_TASK_DEFAULT);

}


void userConfigInition()
{	
	/* ΢�뼶��ʱ֧�� */
	
	#if (!USE_TIME_BASE_REG)
	udelay_module_init();
	#endif
	
	/* CPU֧�� */
	
	cpu_up_sync(CPU_NUMBER);
	
	
	
	/* �˼�ʱ��ͬ�� */
	
	extern void cores_time_sync();
	cores_time_sync();
	
	/* ����ģ�� */
	
	fsmgr_module_init();
	#ifndef REWORKS_MIN_CONFIG
	typedef void(*PRINT_REWORKS_LOGO)(const char *fmt, ...);
	extern PRINT_REWORKS_LOGO reworks_logo_show_printx;
	reworks_logo_show_printx = (PRINT_REWORKS_LOGO)printf;
	#endif
	
	
	/* ��չģ�� */
	
	io_module_init();
	
	/* TTYģ�� */
	
	tty_module_init();
	
	/* ����ģ�� */
	
	buf_module_init();
	
	/* ��ǿ������Э��ջ */
	
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
	
	
	/* DOS�ļ�ϵͳ */
	
	dosfs_module_init(DOSFS_CACHE_SIZE, DOSFS_MAX_FD_NUM);
	shmFsLibInit("/shm");
	
	/* PCI���� */
	
	pci_config_init(PCI_MECHANISM, (int)sys_pci_config_read,(int)sys_pci_config_write,0);
	sys_pci_auto_config();
	
	/* ����ģ�� */
	
	
	serial_module_init();
	
	
	/* ͼ��ϵͳ���� */
	
	if(GRAPHICS_GPU_DEVICE_OPEN == true)
	{	
	extern void (*gfxdriver_init_funcs)(void);// �����豸����ָ������
	extern void directfb_780E2d_ctor();
	gfxdriver_init_funcs = directfb_780E2d_ctor; 
	
	gpu_device_number = 3;
	}
	else
	gpu_device_number = 0;
	
	/* ��ʾ���� */
	
	video_setup(FB_DEVICE_RESOLVE,FB_DEVICE_DEPTH,FB_DEVICE_NAME);
	ls2h_cursor_init(); 
	initbase();
	
	/* PCI����֧�� */
	
	pci_module_init();

}


#endif /* CONFIGURE_INIT */

#ifdef __cplusplus
}
#endif

#endif /* REDE_CONFIGURATION_H_INCLUDED__ */
