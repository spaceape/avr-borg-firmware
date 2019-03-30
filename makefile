
export SYSTEM=avr
export CC=avr-g++
export MCU=atmega328p
export SYSROOT=
export BASE_DIR=$(PWD)
export DIST_DIR=$(PWD)/dist
export BUILD_TYPE=
export BUILD_DIR=

ifeq ($(BUILD_TYPE),)
	BUILD_TYPE=debug
	OPTIM=-Os
else ifeq ($(BUILD_TYPE),debug)
	BUILD_TYPE=debug
	OPTIM=-Os
else ifeq ($(BUILD_TYPE),optim)
	BUILD_TYPE=optim
	OPTIM=-O2 -flto
endif

ifeq ($(BUILD_DIR),)
	BUILD_DIR=$(BASE_DIR)/base/$(BUILD_TYPE)
endif

export CCFLAGS=\
 -fno-rtti -fno-exceptions -fno-threadsafe-statics -fno-leading-underscore -fomit-frame-pointer -fno-asynchronous-unwind-tables\
 -Wall -Wextra -Wpedantic $(OPTIM) -std=c++2a
export SYSFLAGS=-mmcu=$(MCU)
export INCLUDES=-I$(BASE_DIR)/include -I$(BASE_DIR)/src
export DEFS=-DF_CPU=16000000
export ASFLAGS=
export LDFLAGS=-flto -Wall -Wextra
export VERSION=0.0.1

ifeq ($(DEV),)
	DEV=/dev/ttyUSB0
endif

all: src

src:
	$(MAKE) --directory src all

install:
	$(MAKE) --directory src install

borg-$(SYSTEM)-firmware-$(VERSION).hex: src makefile
	avr-objcopy -j .text -j .data -O ihex src/borg-$(SYSTEM)-firmware-$(VERSION).bin $@

flash: borg-$(SYSTEM)-firmware-$(VERSION).hex
	 avrdude -p$(MCU) -V -carduino -P$(DEV) -b57600 -v -U flash:w:$<

clean:
	$(MAKE) --directory src clean
	rm -fv borg-$(SYSTEM)-firmware-$(VERSION).hex

.PHONY: all src install iso clean
