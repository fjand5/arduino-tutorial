#include "esp_log.h"
#include "esp_system.h"
static const char *TAG = "main";
void LOG_TO_STRING(const char *fmt, va_list _args)
{
   va_list args = _args;
   
   
   printf("\033[96;1m my log: ");
   int size_string = vsnprintf(NULL, 0, fmt, args);
   char *string = (char *)malloc(size_string);
   vsnprintf(string, size_string, fmt, args);
   printf(string);
   printf("\033[0m\n");
   // return vprintf(fmt, args);
}
void app_main(void)
{
   esp_log_set_vprintf(&LOG_TO_STRING);
   ESP_LOGE(TAG, "ESP_LOGE %d\n", 1);
   ESP_LOGW(TAG, "ESP_LOGW %d\n", 2);
   ESP_LOGI(TAG, "ESP_LOGI %d\n", 3);
   ESP_LOGD(TAG, "ESP_LOGD %d\n", 4);
   ESP_LOGV(TAG, "ESP_LOGV %d\n", 5);
}
