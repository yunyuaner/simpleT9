################################################################################
# �Զ����ɵ��ļ�. ��Ҫ���б༭!
################################################################################

-include $(ROOT)/user.mk

# ����Щ���ߵ��õ��������������������
C_SRCS += \
../../usrInit.c 

OBJS += \
./usrInit.o 

C_DEPS += \
./usrInit.d 


# ÿ����Ŀ¼�����ṩ��������Ĺ���Դ�Ĺ���
%.o: ../../%.c
	@echo_rede '�����ļ�: $<'
	@echo_rede '����: GCC C Compiler'
	mipsel-elf-gcc -O0 -g -Wall -c -fmessage-length=0 $(CONFIG_COMPLILE_FLAGS) $(CPPFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$@" -o"$@" "$<"
	@echo_rede '��ɹ���: $<'
	@echo_rede ' '


