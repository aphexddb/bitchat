CC=gcc
CFLAGS=-Ivendor/libsodium/include -Wall -Wextra -O2
LDFLAGS=vendor/libsodium/lib/libsodium.a
TARGET=bitchat
SRC=src/main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(TARGET)

.PHONY: all clean
