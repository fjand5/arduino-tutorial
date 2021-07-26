
#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 1;             // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
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


void setupNRF() {
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
  {
    Serial.println("Cannot communicate with radio");
    while (1); // Wait here forever.
  }

  _radioData.FromRadioId = RADIO_ID;
  Serial.println("Success");
}

void loopNRF() {

  _radioData.OnTimeMillis = millis();

  for (int i = 0; i < NUM_OF_BUTTON; i++) {
    if (!button[i].isSent) {
      _radioData.cmd = button[i].cmd;
      button[i].isSent = _radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData));
      String res;
      res = button[i].isSent ? String("Sent") : String("Failed");
      Serial.println(res);
    }
  }
}
