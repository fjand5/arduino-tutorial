#define CMD_TOGGLE 1
#define BUTTON_PIN 2
#include <EasyButton.h>
class RemoteButton: public EasyButton {
  public:
    bool isSent = true;
    uint8_t cmd;
    using EasyButton::EasyButton;
};
RemoteButton button(BUTTON_PIN);

void setupBUTTON() {

  button.begin();
  button.cmd = CMD_TOGGLE;
  button.onPressed([]() {
    button.isSent = false;
  });
}

void loopBUTTON() {
  button.read();
}
