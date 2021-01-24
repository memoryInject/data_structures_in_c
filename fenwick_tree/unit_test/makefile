C_COMPILER=gcc

CLEANUP = rm -rf
MKDIR = mkdir -p
TARGET_EXTENSION=.out

UNITY_ROOT=../../unit_test_src

# CFLAGS=-std=c89
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
#CFLAGS += -Wno-misleading-indentation

TARGET_BASE1=fenwickTreeTest
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
SRC_FILES1=$(UNITY_ROOT)/unity.c fenwickTreeTest.c  ../fenwickTree.c 

INC_DIRS=-Isrc -I$(UNITY_ROOT) -I../
SYMBOLS=

all: default clean

default: $(SRC_FILES1) 
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1)
	- ./$(TARGET1)

clean:
	$(CLEANUP) $(TARGET1)

.PHONY: all clean
