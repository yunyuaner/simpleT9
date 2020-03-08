/*******************************************************************************
 * 
 * ��Ȩ��             �й����ӿƼ����Ź�˾����ʮ���о���
 * ������            ���ļ�����������ReWorks����ϵͳ����ͷ�ļ��ͺ궨�壬���ļ���usrInit.cʹ��
 * 
 * �Զ����ɵ��ļ��� ��Ҫ���б༭
 * 
 */

#define SYS_TICKS_PER_TIMESLICE		5
#define SYS_TICKS_PER_SEC		100

#define INCLUDE_MQUEUE
#define REWORKS_MAX_MSGQS		1024

#define INCLUDE_PTHREAD_COND
#define REWORKS_MAX_CONDS		1024

#define INCLUDE_PCI_CONFIG

#define ABI_N32
#define CPU_NUMBER		4

#define INCLUDE_3A

#define INCLUDE_MEMORY
#define SYS_KERNEL_MEM_SIZE		64
#define SYS_MEM_SIZE		2048
#define SYS_MEM_START_ADDRESS		0x80000000
#define USR_MEM_INIT_SIZE		128
#define USR_MEM_INCR_SIZE		2

#define INCLUDE_RTC

#define INCLUDE_USER_HEAP
#define REWORKS_HEAP_ALGORITHM		1

#define INCLUDE_OBJECT

#define INCLUDE_EXC_CSP

#define INCLUDE_TTY_MODULE

#define INCLUDE_SERIAL

#define INCLUDE_RTP
#define REWORKS_RTPS_MAX		256
#define KERNEL_MM_METHOD		1
#define PCI_MECHANISM		0
#define USE_TIME_BASE_REG		1

#define INCLUDE_REGUI_2D

#define INCLUDE_STD_IO_DEV
#define STD_INPUT_DEVICE_NAME		"/dev/serial0"
#define STD_OUTPUT_DEVICE_NAME		"/dev/serial0"
#define ISR_NESTABLE		1
#define FPU_SAVECTX_ENABLE		1

#define INCLUDE_PTHREAD_HOOK

#define INCLUDE_PTHREAD_MUTEX
#define REWORKS_MAX_MUTEXES		1024
#define FB_DEVICE_DEPTH		16
#define FB_DEVICE_NAME		"/dev/fb0"
#define FB_DEVICE_RESOLVE		"1024x768"

#define INCLUDE_DOSFS
#define DOSFS_CACHE_SIZE		131072
#define DOSFS_MAX_FD_NUM		100

#define INCLUDE_IPNET
#define IPNET_MEMORY_LIMIT		16
#define IPNET_TIMEOUT_JOB_PRIO		2
#define IPNET_REASSEMBLY_TIMEOUT		60
#define IPNET_URGENT_COLLECTION		1

#define INCLUDE_KERNEL_PTHREAD
#define REWORKS_MAX_TASKS		1024

#define INCLUDE_VXWORKS_TASK
#define VX_FP_TASK_DEFAULT		0

#define INCLUDE_MMU_CONFIG

#define INCLUDE_PTHREAD_SPECIFIC
#define REWORKS_MAX_KEYS		1024

#define INCLUDE_EVENT

#define INCLUDE_IO_MODULE

#define INCLUDE_BUF

#define INCLUDE_MEM_PART
#define REWORKS_MAX_MPARTS		128

#define INCLUDE_TIME_SYNC

#define INCLUDE_SEMAPHORE
#define REWORKS_MAX_SEMS		1024
#define GRAPHICS_KBD_DEVICE_NAME		"/dev/ukbd0"
#define GRAPHICS_MSE_DEVICE_NAME		"/dev/umse0"
#define GRAPHICS_KBD_DEVICE_TYPE		2
#define GRAPHICS_MSE_DEVICE_TYPE		2
#define GRAPHICS_GPU_DEVICE_OPEN		0
#define GRAPHICS_TOUCH_SCREEN_DEVICE_NAME		"/dev/ts"


