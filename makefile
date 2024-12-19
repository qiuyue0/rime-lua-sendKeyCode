CC = gcc
CFLAGS = -Ilua -lrime -L.

SRC = sendKeyCode.c keycodes.c
OBJ = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
    LIBS = -luser32
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
	RM = rm -f
	FIX_PATH = $1
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean_all:
	$(RM) $(call FIX_PATH,$(OBJ),$(TARGET))
clean:
	$(RM) $(call FIX_PATH,$(OBJ))

.PHONY: all clean
