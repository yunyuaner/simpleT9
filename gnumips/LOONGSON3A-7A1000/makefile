################################################################################
# 自动生成的文件. 不要进行编辑!
################################################################################

ROOT := ..

REDE_HOME := C:/ReDeV5.1.2-LS3A-RTP-a190726

PROJ_PATH := C:\ReDeV5.1.2-LS3A-RTP-a190726\workspace\simpleT9

CONFIG_LD_FLAGS :=  \
				-B"$(PROJ_PATH)"

TOOLCHAIN_PREFIX := gnumips

CPUARCH_PREFIX := mipsel

RM := rm -rf

ZIP_CLEAN := *.o zreworks.elf reworks.bin.gz

OUTPUT_PATH = $(shell pwd)

CPPFLAGS := 



LDFLAGS := 



LD_OBJS = $(OBJS)

# 参与构建的所有源都在此定义
-include ../../makefile.conf
-include sources.mk
-include subdir.mk
-include ime/subdir.mk
-include data/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_UPPER_DEPS)),)
-include $(C++_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(O_DEPS)),)
-include $(O_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_UPPER_DEPS)),)
-include $(CPP_UPPER_DEPS)
endif
ifneq ($(strip $(OBJ_DEPS)),)
-include $(OBJ_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CC_UPPER_DEPS)),)
-include $(CC_UPPER_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_UPPER_DEPS)),)
-include $(CXX_UPPER_DEPS)
endif
endif


# 从这些工具调用到构建变量添加输入和输出
EXECUTABLES += \
reworks.elf \
reworks.bin \

PGM += \
simpleT9.obj \


# 所有目标
ifndef CROSS_PREFIX
all:
	@echo_rede 此项目的构建配置为：gnumips，没有找到相应的系统资源配置与之匹配，请先打开“系统资源配置”编辑页，选择所需的系统资源配置并保存。
else ifneq ($(TOOLCHAIN_PREFIX),$(CROSS_PREFIX))
all:
	@echo_rede 此项目的构建配置为：gnumips，但当前相应的系统资源配置为非“$(TOOLCHAIN_PREFIX)”目标平台，请选择匹配的系统资源配置。
else
all: reworks.elf secondary-outputs
endif

# 工具调用
reworks.elf: $(PGM)
	@echo_rede '构建目标: $@'
	@echo_rede '调用: GCC objcopy Tool'
	mipsel-elf-objcopy --strip-unneeded -R ".pdr" $(PGM)  "reworks.elf"
	@echo_rede ""
	@echo_rede 'Size of $@:'
	@mipsel-elf-size "$@"
	@echo_rede '完成构建目标: $@'
	@echo_rede ' '

reworks.bin: $(PGM)
	mipsel-elf-objcopy --strip-unneeded -R ".pdr" -O binary $(PGM)  "reworks.bin"
	@echo_rede ' '

simpleT9.obj: $(LD_OBJS) $(OBJS)
	@echo_rede '调用: GCC C++ Linker'
	mipsel-elf-g++ $(LDFLAGS) $(CONFIG_LD_FLAGS) $(LD_OBJS) -o "simpleT9.obj" $(LIBS_USR) $(USER_OBJS) -Wl,--start-group $(LIBS_CFG) -Wl,--end-group
	@echo_rede '完成构建: $@'
	@echo_rede ' '

# 其它目标
clean:
	-$(RM) $(ZIP_CLEAN) $(OTHER_CLEAN)$(C++_UPPER_DEPS)$(OBJS)$(C_DEPS)$(O_DEPS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(ASM_UPPER_DEPS)$(CPP_UPPER_DEPS)$(OBJ_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(PGM)$(CC_UPPER_DEPS)$(C_UPPER_DEPS)$(CXX_UPPER_DEPS) reworks.elf
	-@echo_rede ' '

secondary-outputs: $(EXECUTABLES)

.PHONY: all clean dependents
.SECONDARY:

