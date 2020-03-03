################################################################################
# 自动生成的文件. 不要进行编辑!
################################################################################

-include $(ROOT)/ime/user.mk

# 从这些工具调用到构建变量添加输入和输出
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


# 每个子目录必须提供它所参与的构建源的规则
ime/%.o: ../../ime/%.cpp
	@echo_rede '构建文件: $<'
	@echo_rede '调用: GCC C++ Compiler'
	mipsel-elf-g++ -O0 -g -Wall -c -fmessage-length=0 -std=c++0x $(CONFIG_COMPLILE_FLAGS) $(CPPFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$@" -o"$@" "$<"
	@echo_rede '完成构建: $<'
	@echo_rede ' '


