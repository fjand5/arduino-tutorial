// ================== file button.ino ============================
#include <EasyButton.h>
EasyButton leftBtn(4, 75);
EasyButton selectBtn(3, 75);
EasyButton rightBtn(2, 75);
void setupBUTTON() {
  leftBtn.begin();
  selectBtn.begin();
  rightBtn.begin();
  leftBtn.onPressed([]() {
    if (showTimeFlag == true) {
      showTimeFlag = false;
      displayMenu();
      return;
    }

    prevMenu();
  });
  selectBtn.onPressed([]() {
    if (showTimeFlag == true) {
      showTimeFlag = false;
      displayMenu();
      return;
    }
    selectMenu();
  });
  rightBtn.onPressed([]() {
    if (showTimeFlag == true) {
      showTimeFlag = false;
      displayMenu();
      return;
    }
    nextMenu();
  });
}

void loopBUTTON() {
  leftBtn.read();
  selectBtn.read();
  rightBtn.read();
}
