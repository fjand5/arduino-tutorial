#define NUM_OF_BUTTON 4

#define CMD_ON_LED_1 1
#define CMD_OFF_LED_1 2
#define CMD_ON_LED_2 3
#define CMD_OFF_LED_2 4

#define BUTTON_PIN_ON_LED_1 2
#define BUTTON_PIN_OFF_LED_1 3
#define BUTTON_PIN_ON_LED_2 4
#define BUTTON_PIN_OFF_LED_2 5
#include <EasyButton.h>
class RemoteButton: public EasyButton {
  public:
    bool isSent = true;
    uint8_t cmd;
    using EasyButton::EasyButton;
};
RemoteButton button[] = {
  RemoteButton(BUTTON_PIN_ON_LED_1),
  RemoteButton(BUTTON_PIN_OFF_LED_1),
  RemoteButton(BUTTON_PIN_ON_LED_2),
  RemoteButton(BUTTON_PIN_OFF_LED_2),

};
void setupBUTTON() {
  for (int i = 0; i < NUM_OF_BUTTON; i++) {
    button[i].begin();
  }
  button[0].cmd = CMD_ON_LED_1;
  button[1].cmd = CMD_OFF_LED_1;
  button[2].cmd = CMD_ON_LED_2;
  button[3].cmd = CMD_OFF_LED_2;
  
  button[0].onPressed([]() {
    button[0].isSent = false;
  });
  button[1].onPressed([]() {
    button[1].isSent = false;
  });
  button[2].onPressed([]() {
    button[2].isSent = false;
  });
  button[3].onPressed([]() {
    button[3].isSent = false;
  });
}

void loopBUTTON() {
  
  for (int i = 0; i < NUM_OF_BUTTON; i++) {
    button[i].read();
  }
}
