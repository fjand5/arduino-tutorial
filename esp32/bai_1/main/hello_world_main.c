#include "esp_log.h"
#include "esp_system.h"
static const char *TAG = "main";
void myLogger(const char *str, va_list arg)
{
   printf("\033[35;1mLog của tui\033[0m\n");

   int mIndex = 0;
   bool isCL = false;
   if (str[0] == '\033')
   {
      isCL = true;
   }
   while (str[mIndex] != 0 && str[mIndex] != 'm')
   {
      mIndex++;
   }
   mIndex++;
   int len = vsnprintf(NULL, 0, str, arg);
   char *data; 
   if (isCL)
   {
      data = (char *)malloc(len - mIndex + 1);
      vsnprintf(data, len, str + mIndex, arg);
   }else{
      data = (char *)malloc(len + 2);
      vsnprintf(data, len + 1, str, arg);
   }
   printf(data);
}
void app_main(void)
{
   esp_log_set_vprintf(myLogger);
   ESP_LOGE(TAG, "ESP_LOGE");
   ESP_LOGW(TAG, "ESP_LOGW");
   ESP_LOGI(TAG, "ESP_LOGI");
   ESP_LOGD(TAG, "ESP_LOGD");
   ESP_LOGV(TAG, "ESP_LOGV");
}
