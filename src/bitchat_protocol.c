#include "bitchat_protocol.h"
#include <stdio.h>

static uint64_t read_u64_be(const uint8_t *buf)
{
    uint64_t v = 0;
    for (int i = 0; i < 8; i++) {
        v = (v << 8) | buf[i];
    }
    return v;
}

int bitchat_decode_packet(struct bitchat_packet *pkt, const uint8_t *data, size_t len)
{
    if (!pkt || !data || len < 13) { // minimal header
        return -1;
    }

    size_t offset = 0;
    pkt->version = data[offset++];
    pkt->type    = data[offset++];
    pkt->ttl     = data[offset++];

    pkt->timestamp = read_u64_be(data + offset);
    offset += 8;

    uint8_t flags = data[offset++];
    int has_recipient = flags & 0x01;
    pkt->has_recipient = has_recipient;

    uint16_t payload_len = (data[offset] << 8) | data[offset+1];
    offset += 2;

    if (len < offset + 8 + (has_recipient ? 8 : 0) + payload_len) {
        return -1;
    }

    for (int i = 0; i < 8; i++) {
        pkt->sender_id[i] = data[offset+i];
    }
    offset += 8;

    if (has_recipient) {
        for (int i = 0; i < 8; i++) {
            pkt->recipient_id[i] = data[offset+i];
        }
        offset += 8;
    }

    pkt->payload_len = payload_len;
    if (payload_len > BITCHAT_MAX_PAYLOAD) {
        payload_len = BITCHAT_MAX_PAYLOAD;
    }
    for (size_t i = 0; i < payload_len; i++) {
        pkt->payload[i] = data[offset+i];
    }
    return 0;
}

void bitchat_print_packet(const struct bitchat_packet *pkt)
{
    if (!pkt) return;
    printf("BitChat packet\n");
    printf("  version: %u\n", pkt->version);
    printf("  type: 0x%02X\n", pkt->type);
    printf("  ttl: %u\n", pkt->ttl);
    printf("  timestamp: %llu\n", (unsigned long long)pkt->timestamp);
    printf("  sender: ");
    for (int i = 0; i < 8; i++) printf("%02X", pkt->sender_id[i]);
    printf("\n");
    if (pkt->has_recipient) {
        printf("  recipient: ");
        for (int i = 0; i < 8; i++) printf("%02X", pkt->recipient_id[i]);
        printf("\n");
    }
    printf("  payload (%zu bytes): ", pkt->payload_len);
    for (size_t i = 0; i < pkt->payload_len; i++) printf("%02X", pkt->payload[i]);
    printf("\n");
}
