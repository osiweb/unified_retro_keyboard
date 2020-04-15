# -*- makefile -*-

ARCH ?= atmega2560
TARGET_KEYMAP ?= production
TARGET_MAKEFILE ?= Makefile.$(ARCH)

BUILD_DIR = ../build

all: app

app:
	make -f $(TARGET_MAKEFILE)

test:
	make -f Makefile.test 

clean:
	make -f $(TARGET_MAKEFILE) clean
	make -f Makefile.test clean

cleanall:
	make -f $(TARGET_MAKEFILE)
cleanall
	make -f Makefile.test cleanall

