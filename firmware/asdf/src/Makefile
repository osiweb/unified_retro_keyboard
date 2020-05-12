# -*- makefile -*-

ARCH ?= atmega2560
KEYMAP ?= production
TARGET_MAKEFILE ?= Makefile.app

BUILD_DIR = ../build

all: app

app:
	make -f $(TARGET_MAKEFILE) ARCH=$(ARCH) KEYMAP=$(KEYMAP)y

test:
	make -f Makefile.test 

clean:
	make -f $(TARGET_MAKEFILE) clean
	make -f Makefile.test clean

cleanall:
	make -f $(TARGET_MAKEFILE) cleanall
	make -f Makefile.test cleanall

