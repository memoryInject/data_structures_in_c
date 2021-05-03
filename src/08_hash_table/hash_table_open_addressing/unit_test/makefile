C_COMPILER=gcc

CLEANUP = rm -rf
MKDIR = mkdir -p
TARGET_EXTENSION=.out

UNITY_ROOT=../../../../libs/unity

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

BASE_TARGET_NAME=hashTableOpenAddressingBase

TARGET_BASE1=hashTableLinearProbingTest
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
SRC_FILES1=$(UNITY_ROOT)/unity.c $(TARGET_BASE1).c  ../$(BASE_TARGET_NAME).c 

TARGET_BASE2=hashTableQuadraticProbingTest
TARGET2 = $(TARGET_BASE2)$(TARGET_EXTENSION)
SRC_FILES2=$(UNITY_ROOT)/unity.c $(TARGET_BASE2).c  ../$(BASE_TARGET_NAME).c 

TARGET_BASE3=hashTableDoubleHashingTest
TARGET3 = $(TARGET_BASE3)$(TARGET_EXTENSION)
SRC_FILES3=$(UNITY_ROOT)/unity.c $(TARGET_BASE3).c  ../$(BASE_TARGET_NAME).c 


INC_DIRS=-Isrc -I$(UNITY_ROOT) -I../
SYMBOLS=

all: linearProbing quadraticProbing doubleHashing clean

linearProbing: $(SRC_FILES1) 
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1)
	- ./$(TARGET1)

quadraticProbing: $(SRC_FILES2) 
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES2) -o $(TARGET2)
	- ./$(TARGET2)
	
doubleHashing: $(SRC_FILES3) 
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES3) -o $(TARGET3)
	- ./$(TARGET3)

clean:
	$(CLEANUP) $(TARGET1) $(TARGET2) $(TARGET3)

.PHONY: all clean
