CC:=gcc
CC_FLAGS:=-O3
SRC_FILE:=main.c

NAME:=wwmmchksum # WarioWare Mega Microgames CHecKSUM

TARGET:=$(NAME).out

ifdef OS
	TARGET:=$(NAME).exe
endif

build:
	$(CC) $(SRC_FILE) $(CC_FLAGS) -o $(TARGET)
