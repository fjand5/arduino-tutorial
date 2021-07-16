
// ================== file menu.ino ============================
#include <MenuSystem.h>
class MyRenderer : public MenuComponentRenderer {
  public:
    void render(Menu const& menu) const {
      clearLCD();
      printLCD(0, 0, menu.get_name());
      menu.get_current_component()->render(*this);
    }

    void render_menu_item(MenuItem const& menu_item) const {
      printCenterLCD(1, menu_item.get_name());
    }

    void render_back_menu_item(BackMenuItem const& menu_item) const {
    }

    void render_numeric_menu_item(NumericMenuItem const& menu_item) const {
      if (menu_item.has_focus()) {
        clearLCD();
        printLCD(0, 0, menu_item.get_name());
        String str;
        if (menu_item.get_value() > menu_item.get_min_value()) {
          str += "<";
        }
        str += menu_item.get_formatted_value();
        if (menu_item.get_value() < menu_item.get_max_value()) {
          str += ">";
        }
        printCenterLCD(1, str);

      } else {
        render_menu_item(menu_item);
      }
    }

    void render_menu(Menu const& menu) const {
      clearLCD();
      printLCD(0, 0, menu.get_name());
      String ret = "";
      for (int i = 0; i < menu.get_num_components(); i++) {
        ret += String(menu.get_menu_component(i)->get_name()) + "  ";
      }
      printLCD(0, 1, ret);
    }
};
MyRenderer my_renderer;

MenuSystem ms(my_renderer);

MenuItem backMni("Back", [](MenuComponent* p) {
  ms.back();
  ms.display();
});
MenuItem exitMni("Exit", [](MenuComponent* p) {
  showTimeFlag = true;
});

Menu daysMnu("Edit Days");
Menu timesMnu("Edit Time");


void nextMenu() {
  ms.next(true);
  ms.display();
}

void prevMenu() {
  ms.prev(true);
  ms.display();
}

void selectMenu() {
  ms.select();
  ms.display();
}

void displayMenu() {
  ms.display();
}

void setupMENU() {
  ms.get_root_menu().set_name("Menu");
  ms.get_root_menu().add_menu(&daysMnu);
  ms.get_root_menu().add_item(new MenuItem("Sun/Lunar",[](MenuComponent* p) {
      showLunarFlag = !showLunarFlag;
  }));
  daysMnu.add_item(
  new NumericMenuItem("Day", nullptr, getDay(), 0, 31, 1, [](float val) {
    setDay(int(val));
    return String(int(val));
  })
  );
  daysMnu.add_item(
  new NumericMenuItem("Month", nullptr, getMonth(), 1, 12, 1, [](float val) {
    setMonth(int(val));
    return String(int(val));
  }));
  daysMnu.add_item(
  new NumericMenuItem("Year", nullptr, getYear(), 00, 99, 1, [](float val) {
    setYear(int(val));
    return String(int(val));
  }));
  //
  ms.get_root_menu().add_menu(&timesMnu);
  timesMnu.add_item(new NumericMenuItem("Hour", nullptr, getHours(), 00, 23, 1, [](float val) {
    setHours(int(val));
    return String(int(val));
  }));
  timesMnu.add_item(new NumericMenuItem("Minutes", nullptr, getMinutes(), 00, 59, 1, [](float val) {
    setMinutes(int(val));
    return String(int(val));
  }));
  timesMnu.add_item(new NumericMenuItem("Seconds", nullptr, getSeconds(), 00, 59, 1, [](float val) {
    setSeconds(int(val));
    return String(int(val));
  }));

  ms.get_root_menu().add_item(&exitMni);
  daysMnu.add_item(&backMni);
  timesMnu.add_item(&backMni);
  ms.display();
}

void loopMENU() {
}
