# bitchat

This repository contains a minimal hello world written in C. It demonstrates a basic setup
using [libsodium](https://github.com/jedisct1/libsodium) for cryptographic primitives and
includes a vendored copy of the ESP-IDF template.

## Building

The project uses `make` with `gcc`. The only dependency is the vendored
`libsodium` library located under `vendor/libsodium`.

To build the hello world executable run:

```sh
make
```

This will produce the `bitchat` binary.
