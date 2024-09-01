OBJS_DIR = build

SRC_DIR = src
DRIVERS_SRC = drivers/src
UTILS_SRC = utils/src
EXT_SRC = ext_modules/src

INC_DIR = inc
DRIVERS_INC = drivers/inc
UTILS_INC = utils/inc
EXT_INC = ext_modules/inc

vpath %.c $(SRC_DIR)
vpath %.c $(DRIVERS_SRC)
vpath %.c $(UTILS_SRC)
vpath %.c $(EXT_SRC)
vpath %.o $(OBJS_DIR)

PROJECT_NAME = stm32_drivers
CC = arm-none-eabi-
CFLAGS = -mcpu=cortex-m3 -g -O0 -ffreestanding -mthumb -mfloat-abi=soft -fdata-sections -ffunction-sections
INCS = -I $(INC_DIR) -I $(DRIVERS_INC) -I $(UTILS_INC) -I $(EXT_INC)
LIBS = 
SRC := $(wildcard *.c) $(wildcard $(SRC_DIR)/*.c) $(wildcard $(DRIVERS_SRC)/*.c) $(wildcard $(UTILS_SRC)/*.c) $(wildcard $(EXT_SRC)/*.c)
OBJ := $(addprefix $(OBJS_DIR)/, $(notdir $(SRC:.c=.o)))
AS = $(wildcard *.s)
AsOBJ = $(addprefix $(OBJS_DIR)/, $(notdir $(AS:.s=.o)))

.PHONY: flash
flash: build
	openocd -f stlink.cfg -c "program $(PROJECT_NAME).elf verify reset exit"

.PHONY: build
build: build_dir $(PROJECT_NAME).bin

$(OBJS_DIR)/%.o: %.c
	$(CC)gcc $< -c $(INCS) -o $@  $(CFLAGS)

$(OBJS_DIR)/%.o: %.s
	$(CC)as $< -o $@ 

$(PROJECT_NAME).elf: $(OBJ) $(AsOBJ)
	$(CC)gcc -T STM32F103C6TX_FLASH.ld $(AsOBJ) $(OBJ) -o $@ -mcpu=cortex-m3 -mthumb -Wl,--gc-sections

$(PROJECT_NAME).bin: $(PROJECT_NAME).elf
	$(CC)objcopy -O binary $< $@

clean:
	rm *.elf -f
	rm *.bin -f
	rm build/*.o -f
	rm *.map -f

.PHONY: rebuild
rebuild: clean build

.PHONY: build_dir
build_dir:
	mkdir -p build