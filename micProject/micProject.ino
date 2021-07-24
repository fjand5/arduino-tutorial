#include "mic.h"
void setup() {
  // delay(10000);
  Serial.begin(115200);
  //sampling_period_us = round(1000000 * (1.0 / samplingFrequency));

  setupMIC();
  setupLEDS();
  Serial.println("booted...");
}
void loop() {
  loopLEDS(map(getValByFreq(),0,100,0,2000));
  // setVol();
  // Serial.println();
  // uint16_t freq =0;
  // double maxValByFreq = 0;
  //  for (int i = 2; i < samples/2; i++) {
  //    if(vReal[i]>maxValByFreq){
  //       maxValByFreq = vReal[i];
  //       freq = i;
  //    }

  // }
  // if(maxValByFreq<100000000.0)
  // maxValByFreq=0;
  // maxValByFreq = mapf(maxValByFreq,0.0, 4000000000.0,0.0,100.0);
  //  Serial.println(String(" maxValByFreq ") + (maxValByFreq)); // max: 8e10; noise: 1e8
  //   setVol(maxValByFreq);
}
