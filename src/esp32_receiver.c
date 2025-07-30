#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"
#include "bitchat_protocol.h"

static const char *TAG = "bitchat";

static uint16_t bitchat_handle_table[2];

static const uint8_t service_uuid128[16] = {
    0xF4,0x7B,0x5E,0x2D,0x4A,0x9E,0x4C,0x5A,
    0x9B,0x3F,0x8E,0x1D,0x2C,0x3A,0x4B,0x5C
};
static const uint8_t char_uuid128[16] = {
    0xA1,0xB2,0xC3,0xD4,0xE5,0xF6,0x4A,0x5B,
    0x8C,0x9D,0x0E,0x1F,0x2A,0x3B,0x4C,0x5D
};

static void gatts_write_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if,
                                      esp_ble_gatts_cb_param_t *param)
{
    if (param->write.handle == bitchat_handle_table[1]) {
        bitchat_packet pkt;
        bitchat_decode_packet(&pkt, param->write.value, param->write.len);
        ESP_LOGI(TAG, "Received packet");
        bitchat_print_packet(&pkt);
    }
}

static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if,
                                esp_ble_gatts_cb_param_t *param)
{
    switch (event) {
    case ESP_GATTS_WRITE_EVT:
        gatts_write_event_handler(event, gatts_if, param);
        break;
    default:
        break;
    }
}

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));

    ESP_ERROR_CHECK(esp_bluedroid_init());
    ESP_ERROR_CHECK(esp_bluedroid_enable());

    esp_ble_gatts_register_callback(gatts_event_handler);
    esp_ble_gatts_app_register(0);

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
