################################################################################
# �Զ����ɵ��ļ�. ��Ҫ���б༭!
################################################################################

-include $(ROOT)/data/user.mk

# ����Щ���ߵ��õ��������������������
CPP_SRCS += \
../../data/fontlib_zh.cpp \
../../data/vocabulary.cpp 

OBJS += \
./data/fontlib_zh.o \
./data/vocabulary.o 

CPP_DEPS += \
./data/fontlib_zh.d \
./data/vocabulary.d 


# ÿ����Ŀ¼�����ṩ��������Ĺ���Դ�Ĺ���
data/%.o: ../../data/%.cpp
	@echo_rede '�����ļ�: $<'
	@echo_rede '����: GCC C++ Compiler'
	mipsel-elf-g++ -O0 -g -Wall -c -fmessage-length=0 -std=c++0x $(CONFIG_COMPLILE_FLAGS) $(CPPFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$@" -o"$@" "$<"
	@echo_rede '��ɹ���: $<'
	@echo_rede ' '


