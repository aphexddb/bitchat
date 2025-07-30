# bitchat

bitchat in C for portability to ESP32 devices. Requires libsodium because implementing crypto is dumb.

A decentralized peer-to-peer messaging app that works over Bluetooth mesh networks. No internet required, no servers, no phone numbers. It's the side-groupchat.

## Building

The project uses `make` with `clang`. The only dependency is the
`libsodium` library, available as a system package or prebuilt under
`vendor/libsodium`.

To build the hello world executable run:

```sh
make
```

This will produce the `bitchat` binary.
