# -*- makefile -*-

ARCH ?= atmega328p
KEYMAP ?= ascii

BUILD_DIR = ../build

all: app

app:
	make -f Makefile.app

test:
	make -f Makefile.test 

clean:
	make -f Makefile.app clean
	make -f Makefile.test clean

cleanall:
	make -f Makefile.app cleanall
	make -f Makefile.test cleanall

