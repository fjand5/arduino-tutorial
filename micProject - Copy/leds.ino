#include <WS2812FX.h>
#define LED_COUNT 12
#define LED_PIN 23
#define TIMER_MS 5000
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

unsigned long last_change = 0;
unsigned long now = 0;

void setupLEDS() {
  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSpeed(1000);
  ws2812fx.setColor(0x117BFF);
  ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.start();
}
void setVol(int vol){
  ws2812fx.clear();
  for(int i =0;i<LED_COUNT;i++){
    ws2812fx.setPixelColor(i,ws2812fx.gamma8(vol),0,0);
    ws2812fx.show();
  }
}
void setFreq(double * data){
  ws2812fx.clear();
  for(int i =0;i<LED_COUNT;i++){
    ws2812fx.setPixelColor(i,data[i],0,0);
  }
    ws2812fx.show();
  
}
void loopLEDS() {
  now = millis();

  ws2812fx.service();

  if(now - last_change > TIMER_MS) {
    ws2812fx.setMode((ws2812fx.getMode() + 1) % ws2812fx.getModeCount());
    last_change = now;
  }
}
