#define runEvery(t) for (static uint32_t _lasttime;\
                         (uint32_t)((uint32_t)micros() - _lasttime) >= (t);\
                         _lasttime += (t))
#include "arduinoFFT.h"
const double NOISE = 200000;
const uint16_t samples = 1024;
const double samplingFrequency = 40000;
double vReal[samples];
double vImag[samples];
unsigned int sampling_period_us;
arduinoFFT FFT = arduinoFFT(vReal, vImag, samples, samplingFrequency);



void setup() {
  Serial.begin(115200);
  sampling_period_us = round(1000000 * (1.0 / samplingFrequency));

  setupMIC();
}
void loop() {
  runEvery(sampling_period_us) {
    static int step = 0;
    double val = getMIC();
    val = val < 0 ? -val : val;
    vReal[step] = val;
    vImag[step] = 0;
    step++;
    if (step == samples) {
      step = 0;

      // Compute FFT
      FFT.DCRemoval();
      FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      FFT.Compute(FFT_FORWARD);
      FFT.ComplexToMagnitude();
      double x = 0;
      
//      double maxValInFre =9999999;
//      double curFre =0;
      for (int i = 2; i < (samples / 2); i++) {    // Don't use sample 0 and only first SAMPLES/2 are usable. Each array element represents a frequency bin and its value the amplitude.
//        if (vReal[i] > NOISE) {
//          if(vReal[i] < maxValInFre){
//            maxValInFre = vReal[i];
//            curFre = i;
//            }
          if (i > 100   && i <= 150  )
            x += vReal[i];
//            sum +=x;
//            count ++;
      }
      Serial.println(String("val ") + x); 
    }
  };
}
