################################################################################
# 自动生成的文件. 不要进行编辑!
################################################################################

-include $(ROOT)/data/user.mk

# 从这些工具调用到构建变量添加输入和输出
CPP_SRCS += \
../../data/fontlib_zh.cpp \
../../data/vocabulary.cpp 

OBJS += \
./data/fontlib_zh.o \
./data/vocabulary.o 

CPP_DEPS += \
./data/fontlib_zh.d \
./data/vocabulary.d 


# 每个子目录必须提供它所参与的构建源的规则
data/%.o: ../../data/%.cpp
	@echo_rede '构建文件: $<'
	@echo_rede '调用: GCC C++ Compiler'
	mipsel-elf-g++ -O0 -g -Wall -c -fmessage-length=0 -std=c++0x $(CONFIG_COMPLILE_FLAGS) $(CPPFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$@" -o"$@" "$<"
	@echo_rede '完成构建: $<'
	@echo_rede ' '


