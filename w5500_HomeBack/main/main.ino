/*
  Ping Example

  This example sends an ICMP pings every 500 milliseconds, sends the human-readable
  result over the serial port.

  Requires Adafruit Ethernet 2 library for W5500

  Circuit:
  Ethernet shield attached to hardware SPI
  Ethernet CS pin to pin 8 and reset pin to pin 7

*/

#include <SPI.h>
#include <Ethernet2.h>
#include <ICMPPing.h>
const byte mac[] = { 0x36, 0xF2, 0xCC, 0xF2, 0xE5, 0xC0 };
IPAddress pingAddr(192, 168, 2, 111); // ip address to ping

SOCKET pingSocket = 0;

char buffer [256];
ICMPPing ping(pingSocket, (uint16_t)random(0, 255));

void setup()
{
  // start Ethernet
  Serial.begin(115200);

  initEthernet();
  Serial.println("init success");

}

void loop()
{
  ICMPEchoReply echoReply = ping(pingAddr, 4);
  if (echoReply.status == SUCCESS)
  {
    Serial.println("Ông chủ đã về rồi");

  }
  else
  {
    Serial.println("Ông chủ đi chơi rồi");

  }
  delay(500);
}


bool initEthernet() {

  Serial.println(F("Obtaining Local IP..."));
  bool DHCPsuccess = false;

  while (!DHCPsuccess) {
    if (Ethernet.begin(mac)) {
      Serial.print(F("DHCP IP: "));
      Serial.println(Ethernet.localIP());

      DHCPsuccess = true;
    } else {
      //timed out 60 secs.
      Serial.println(F("Timeout."));
      Serial.println(F("Check Ethernet cable."));
      Serial.println(F("Retring DHCP..."));

    }

  }
}
