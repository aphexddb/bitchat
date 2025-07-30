CC=clang
CFLAGS=-Ivendor/libsodium/include -Iinclude -Wall -Wextra -O2
LDFLAGS=-lsodium
TARGET=bitchat
SRC=src/main.c src/bitchat_protocol.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(TARGET)

.PHONY: all clean
