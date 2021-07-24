#define runEvery(t) for (static uint32_t _lasttime;\
                         (uint32_t)((uint32_t)micros() - _lasttime) >= (t);\
                         _lasttime += (t))
#include "arduinoFFT.h"
const uint16_t samples = 256;
const double samplingFrequency = 10000;
double vReal[samples];
double vImag[samples];
unsigned int sampling_period_us;
arduinoFFT FFT = arduinoFFT(vReal, vImag, samples, samplingFrequency);



void setup() {
  Serial.begin(115200);
  sampling_period_us = round(1000000 * (1.0 / samplingFrequency));

  setupMIC();
  setupLEDS();  
  Serial.println("booted..."); 
}
double maxVal = 1;
void loop() {
  // loopLEDS();
  runEvery(sampling_period_us) {
    static int step = 0;
    double val = getMIC();
    val = val < 0 ? -val : val;
    vReal[step] = val;
    vImag[step] = 0;
    step++;
    maxVal --;
    if (step == samples) {
      step = 0;

      // Compute FFT
      FFT.DCRemoval();
      FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      FFT.Compute(FFT_FORWARD);
      FFT.ComplexToMagnitude();
      // double x = 0;
      // double count = 0;
      // double data[12] ={0};
    //  double maxValInFre =0;
    //  double curFre =0;
// 2 - 510

      // for (int i = 2; i < (samples / 2); i++) { 
      //   if(vReal[i] > maxValInFre){
      //     maxValInFre = vReal[i];
      //     curFre = i;
      //   }
          // if (i >= 3   && i <= 14  ){
          //   data[i-3] += vReal[i];
          // }
      // }
      // for(int i = 0; i<12; i++){
      //   if(data[i]<10000000.00)
      //     data[i]=0;
      //   else
      //   data[i] /= 12000.00;
      // }
      if(FFT.MajorPeak()> maxVal)
        maxVal = FFT.MajorPeak();
      if(maxVal < 1000)
        maxVal =0;
      // Serial.println(String(" val ") + maxVal); 
      setVol(maxVal/20);
      // setFreq(data);
    }
  };
}
