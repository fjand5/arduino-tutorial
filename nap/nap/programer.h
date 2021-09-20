#pragma once
#include "Adafruit_AVRProg.h"
Adafruit_AVRProg avrprog = Adafruit_AVRProg();
#define LED_PROGMODE LED_BUILTIN
#define LED_ERR LED_BUILTIN
image_t image = {
  {"optiboot_atmega328.hex"},
  {"atmega328P"},
  0x950F,
  {0x3F, 0xFF, 0xDE, 0x05},
  {0x0F, 0x0, 0x0, 0x0},
  {0x3F, 0xFF, 0xFF, 0x07},
  32768,
  128,
  {}
};
void setupProg() {
  avrprog.setProgramLED(LED_PROGMODE);
  avrprog.setErrorLED(LED_ERR);
  // avrprog.generateClock();  // on pin 9
  //  avrprog.setSPI(D1, &SPI);
  Serial.println("\nType 'u' or hit BUTTON for next chip");
}

void loopProg(void) {
  //  if(Serial.available()>0){
  //    String data = Serial.readString();
  //    if(data.indexOf("u")>=0)
  //        upload();
  //  }
}
uint32_t index_image =0;
void copyImage(byte b) {
  if(b == 13)
    return;
  image.image_hexcode[index_image++] = b;
}
void uploadProg() {

  if (!avrprog.targetPower(true)) {
    avrprog.error("Failed to connect to target");
  }

  Serial.print(F("\nReading signature: "));
  uint16_t signature = avrprog.readSignature();
  Serial.println(signature, HEX);
  if (signature == 0 || signature == 0xFFFF) {
    avrprog.error(F("No target attached?"));
  }

  const image_t *targetimage = &image;
  if (targetimage->image_chipsig != signature) {
    avrprog.error(F("Signature doesn't match image"));
  }
  Serial.println(F("Found matching chip/image"));

  Serial.print(F("Erasing chip..."));
  avrprog.eraseChip();
  Serial.println(F("Done!"));

  if (!avrprog.programFuses(
        targetimage->image_progfuses)) { // get fuses ready to program
    avrprog.error(F("Programming Fuses fail"));
  }

  if (!avrprog.verifyFuses(targetimage->image_progfuses,
                           targetimage->fusemask)) {
    avrprog.error(F("Failed to verify fuses"));
  }

  if (!avrprog.writeImage(targetimage->image_hexcode,
                          pgm_read_byte(&targetimage->image_pagesize),
                          pgm_read_word(&targetimage->chipsize))) {
    avrprog.error(F("Failed to write flash"));
  }

  Serial.println(F("\nVerifing flash..."));
  if (!avrprog.verifyImage(targetimage->image_hexcode)) {
    avrprog.error(F("Failed to verify flash"));
  }
  Serial.println(F("\nFlash verified correctly!"));

  // Set fuses to 'final' state
  if (!avrprog.programFuses(targetimage->image_normfuses)) {
    avrprog.error("Programming fuses fail");
  }

  if (!avrprog.verifyFuses(targetimage->image_normfuses,
                           targetimage->fusemask)) {
    avrprog.error("Failed to verify fuses");
  } else {
    Serial.println("Fuses verified correctly!");
  }
}
