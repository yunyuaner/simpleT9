/*******************************************************************************
 * 
 * ��Ȩ��             �й����ӿƼ����Ź�˾����ʮ���о���
 * ������            ���ļ�����������ReWorks����ϵͳ����ͷ�ļ��ͺ궨�壬���ļ���usrInit.cʹ��
 * 
 * �Զ����ɵ��ļ��� ��Ҫ���б༭
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
