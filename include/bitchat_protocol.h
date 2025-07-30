#ifndef BITCHAT_PROTOCOL_H
#define BITCHAT_PROTOCOL_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BITCHAT_MAX_PAYLOAD 512

typedef enum {
    BITCHAT_TYPE_ANNOUNCE       = 0x01,
    BITCHAT_TYPE_LEAVE          = 0x03,
    BITCHAT_TYPE_MESSAGE        = 0x04,
    BITCHAT_TYPE_DELIVERY_ACK   = 0x0A,
} bitchat_msg_type_t;

struct bitchat_packet {
    uint8_t  version;
    uint8_t  type;
    uint8_t  ttl;
    uint64_t timestamp;
    uint8_t  sender_id[8];
    uint8_t  recipient_id[8];
    int      has_recipient;
    size_t   payload_len;
    uint8_t  payload[BITCHAT_MAX_PAYLOAD];
};

int bitchat_decode_packet(struct bitchat_packet *pkt, const uint8_t *data, size_t len);
void bitchat_print_packet(const struct bitchat_packet *pkt);

#ifdef __cplusplus
}
#endif

#endif // BITCHAT_PROTOCOL_H
