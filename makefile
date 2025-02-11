CC = gcc
CFLAGS = -Ilua -L.

SRC = sendKeyCode.c keycodes.c
OBJ = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
    LIBS = -luser32 -lrime
	TARGET = sendKeyCode.dll
	RM = del /Q
	FIX_PATH = $(subst /,\,$1)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
        LIBS = -lX11 -lXtst
        TARGET = sendKeyCode.so
    endif
    ifeq ($(UNAME_S), Darwin)
        LIBS = -framework ApplicationServices
        TARGET = sendKeyCode.so
    endif
    LIBS +=  -lrime-lua
	RM = rm -f
	FIX_PATH = $1
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared -fPIC -o $@ $^ $(CFLAGS) $(LIBS) -O2

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	$(RM) $(call FIX_PATH,$(OBJ),$(TARGET))

.PHONY: all clean
