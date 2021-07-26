
#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 0;       // Our radio's id.  The transmitter will send to this id.
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;

struct RadioPacket // Any packet up to 32 bytes can be sent.
{
  uint8_t FromRadioId;
  uint32_t OnTimeMillis;
  uint32_t FailedTxCount;
  uint8_t cmd;
};

NRFLite _radio;
RadioPacket _radioData;

void (*onReciveData)(uint8_t cmd) = NULL;
void setOnReciveData (void (*func)(uint8_t )){
  onReciveData = func;
 }
void setupNRF() {
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
  {
    Serial.println("Cannot communicate with radio");
    while (1); // Wait here forever.
  }
  Serial.println("Success");
}

void loopNRF() {

  while (_radio.hasData())
  {
    _radio.readData(&_radioData); // Note how '&' must be placed in front of the variable name.
    if(onReciveData != NULL){
      onReciveData(_radioData.cmd);
    }
  }
}
