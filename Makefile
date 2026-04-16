# C Medical Management System

TARGET = medical_system.exe
TOOLCHAIN_DIR = mingw64/mingw64/bin
CC = $(TOOLCHAIN_DIR)/x86_64-w64-mingw32-gcc.exe
RM = cmd /c del /Q
CFLAGS = -Wall -Wextra -g -finput-charset=UTF-8 -fexec-charset=GBK

SRC = src/main.c src/common.c src/login.c src/patient.c src/doctor.c src/admin.c src/public.c src/data_storage.c
OBJ = $(SRC:.c=.o)
HEADERS = src/common.h src/login.h src/patient.h src/doctor.h src/admin.h src/public.h src/data_storage.h

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) $(subst /,\,$(OBJ)) 2>nul

.PHONY: all clean

