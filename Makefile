CC      = gcc
CFLAGS  = -Wall -Wextra -O2
TARGET  = bin/neutrino
SRC     = src/neutrino.c

all: $(TARGET)

$(TARGET): $(SRC) | bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

bin:
	@mkdir -p bin

run: $(TARGET)
	sudo ./$(TARGET)

install: $(TARGET)
	install -Dm755 $(TARGET) /usr/local/bin/neutrino

uninstall:
	rm -f /usr/local/bin/neutrino

clean:
	rm -rf bin

.PHONY: all run install uninstall clean