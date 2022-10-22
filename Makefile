CC := gcc
TARGET := forca
CFLAGS := -Wall -Werror -Wextra -O2
LFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC := ./src/*.c

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(TARGET).c $(LFLAGS)

clean: 
	rm $(TARGET)
