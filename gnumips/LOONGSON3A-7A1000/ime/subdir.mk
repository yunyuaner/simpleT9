################################################################################
# �Զ����ɵ��ļ�. ��Ҫ���б༭!
################################################################################

-include $(ROOT)/ime/user.mk

# ����Щ���ߵ��õ��������������������
CPP_SRCS += \
../../ime/globals.cpp \
../../ime/key.cpp \
../../ime/keyboard.cpp \
../../ime/moc_ui.cpp \
../../ime/pager.cpp \
../../ime/ui.cpp 

OBJS += \
./ime/globals.o \
./ime/key.o \
./ime/keyboard.o \
./ime/moc_ui.o \
./ime/pager.o \
./ime/ui.o 

CPP_DEPS += \
./ime/globals.d \
./ime/key.d \
./ime/keyboard.d \
./ime/moc_ui.d \
./ime/pager.d \
./ime/ui.d 


# ÿ����Ŀ¼�����ṩ��������Ĺ���Դ�Ĺ���
ime/%.o: ../../ime/%.cpp
	@echo_rede '�����ļ�: $<'
	@echo_rede '����: GCC C++ Compiler'
	mipsel-elf-g++ -O0 -g -Wall -c -fmessage-length=0 -std=c++0x $(CONFIG_COMPLILE_FLAGS) $(CPPFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$@" -o"$@" "$<"
	@echo_rede '��ɹ���: $<'
	@echo_rede ' '


