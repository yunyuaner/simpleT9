/*******************************************************************************
 * 
 * 版权：             中国电子科技集团公司第三十二研究所
 * 描述：            本文件定义了运行ReWorks操作系统所需头文件和宏定义，该文件被usrInit.c使用
 * 
 * 自动生成的文件。 不要进行编辑
 * 
 */

#ifndef REWORKS_SYSTEM_H_INCLUDED__
#define REWORKS_SYSTEM_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "usrArgs.h"


#include <osconfig.h>

#include "configInition.h"


#if defined(INCLUDE_RTP) && !defined(INCLUDE_SHELL)
#define USER_APP_INIT \
	{	\
	extern int satadev_create(int ctrl, int drive,char *devname);	\
	satadev_create(0, 0, "/dev/ata0a");		\
	mount("dosfs","/dev/ata0ap1","/c");		\
	extern void fork_shell();			\
	fork_shell();	\
	}										
#endif

#ifdef __cplusplus
}
#endif

#endif /* REWORKS_SYSTEM_H_INCLUDED__ */
