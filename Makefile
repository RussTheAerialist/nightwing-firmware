PROJECT_DIR=$(CURDIR)
ARDMK_DIR=$(PROJECT_DIR)/build
ARDUINO_DIR=/Applications/Arduino.app/Contents/Java

USER_LIB_PATH := $(HOME)/Documents/Arduino/libraries/
include $(CURDIR)/board.mk
AVR_TOOLS_DIR = /usr/local
AVRDDUDE = /usr/local/bin/avrdude
CFLAGS_STD = -std=gnu11
CXXFLAGS_STD = -std=gnu++11
CXXFLAGS += -Wall -fno-exceptions

include $(CURDIR)/libraries.mk
MONITOR_PORT = /dev/tty.usbmodem*
CURRENT_DIR = $(shell basename $(CURDIR))

OBJDIR = $(PROJECT_DIR)/bin/$(BOARD_TAG)/$(CURRENT_DIR)

include $(ARDMK_DIR)/Arduino.mk
