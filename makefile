CC:=gcc
CC_FLAGS:=-O3
SRC_FILE:=main.c

# WarioWare Mega Microgames CHecKSUM
NAME:=wwmmchksum

TARGET:=$(NAME).out

ifdef OS
	TARGET:=$(NAME).exe
endif

build:
	$(CC) $(SRC_FILE) $(CC_FLAGS) -o $(TARGET)
