# COLORS
RED=\033[0;31m
GREEN=\033[0;32m
ORANGE=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
LIGHTGRAY=\033[0;37m
DARKGRAY=\033[1;30m
YELLOW=\033[0;33m
NC=\033[0m # No Color

DEBUG ?= 1
export DEBUG
MOTOR_LOOPBACK ?= 0
export MOTOR_LOOPBACK
CAR_LOOPBACK ?= 0
export CAR_LOOPBACK

# Check if test file exists for the leader.
ifneq (,$(wildcard Tests/Test_$(TEST).c))
	TEST_LEADER ?= Tests/Test_$(TEST).c
else
	TEST_LEADER ?= Apps/Src/main.c
endif

LEADER = controls-leader

all:
	@printf "${RED}Not enough arguments. Call: ${ORANGE}make help${NC}\n"

.PHONY: leader
leader: stm32f413

stm32f413:
	@printf "${YELLOW}Compiling for leader...${NC}\n"
	$(MAKE) -C BSP -C STM32F413 -j TARGET=$(LEADER) TEST=$(TEST_LEADER)
	@printf "${BLUE}Compiled for leader! Jolly Good!${NC}\n"

flash:
	$(MAKE) -C BSP -C STM32F413 flash

docs:
	doxygen Docs/doxyfile
	$(MAKE) -C Docs html

help:
	@printf "Format: ${ORANGE}make ${BLUE}<BSP type>${NC}${ORANGE}TEST=${PURPLE}<Test type>${NC}\n"
	@printf "BSP types (required):\n"
	@printf "	${BLUE}stm32f413/leader${NC}\n"
	@printf "\n"
	@printf "Test types (optional):\n"
	@printf "	Set TEST only if you want to build a test.\n"
	@printf "	Otherwise, don't include TEST in the command.\n"
	@printf "	To build a test, replace ${PURPLE}<Test type>${NC} with the name of the file\n"
	@printf "	excluding the file type (.c) e.g. say you want to test Voltage.c, call\n"
	@printf "		${ORANGE}make ${BLUE}stm32f413 ${ORANGE}TEST=${PURPLE}Voltage${NC}\n"


clean:
	rm -fR Objects
	rm -f *.out
	rm -fr Docs/doxygen
	rm -fr Docs/build

tidy:
	$(MAKE) -C BSP -C STM32F413 tidy

format:
	$(MAKE) -C BSP -C STM32F413 format

tidy-check:
	$(MAKE) -C BSP -C STM32F413 tidy-check

format-check:
	$(MAKE) -C BSP -C STM32F413 format-check

check: format-check format tidy-check

