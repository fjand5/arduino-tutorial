#include "esp_log.h"

static const char* TAG ="main";
void app_main(void)
{
   ESP_LOGE(TAG, "ESP_LOGE");
   ESP_LOGW(TAG, "ESP_LOGW");
   ESP_LOGI(TAG, "ESP_LOGI");
   ESP_LOGD(TAG, "ESP_LOGD");
   ESP_LOGV(TAG, "ESP_LOGV");
}
