//
//  main.cpp
//  SimpleStateMachine
//
//  Created by Prashant Gurung on 12/11/2024.
//

#include "PlaySound.h"
#include "Spell.h"
#include <iostream>
#include <ostream>
#include <thread>
#include <unistd.h>
int *returnArray1() {
  static int intArray[] = {1, 2, 4, 6, 8, 10};
  return &intArray[0];
}

int *returnArray2() {
  static int intArray[] = {1, 2, 4, 6, 8, 10};
  return intArray;
}

void sleep(int s) {
  for (int i = s; i >= 0; i = i - 1000) {

    if (i >= 1000) {
      std::cout << i / 1000 << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } else if (i > 0 and i < 1000) {

      std::this_thread::sleep_for(std::chrono::milliseconds(i));
    } else {
    }
  }
}

int main(int argc, const char *argv[]) {

  //    std::cout << returnArray1() << std::endl; // prints 0x100008000
  //    std::cout << returnArray2() << std::endl; // prints 0x100008018
  //    std::cout << returnArray1()[0] << std::endl; // prints 1
  //    std::cout << returnArray2()[0] << std::endl; // prints 1
  //    std::cout << "" << std::endl;
  //
  // std::cout << " Time point value " <<
  // std::chrono::system_clock::time_point{}          << std::endl;

  Spell tornado({15.0f, 5.0f, 2.0f, 1.0f});
  tornado.learnSpell(nullptr);

  tornado.castSpell(nullptr);
  //  hex.useRefresher();
  //  if (hex.onCoolDown())
  //    std::cout << "Yes On Cooldown " << std::endl;
  //  else
  //    std::cout << "Not On Cooldown " << std::endl;
  //
  //  hex.castSpell(nullptr);
  //  hex.castSpell(nullptr);
  //
  //  hex.print_SpellTimes();
  //  hex.setOctarine(true);
  //  hex.print_SpellTimes();
  //  hex.setOctarine(false);
  //  hex.print_SpellTimes();

  sleep(4000);
  tornado.learnSpell(nullptr);
  tornado.castSpell(nullptr);

  sleep(3000);
  tornado.castSpell(nullptr);

  tornado.learnSpell(nullptr);
  sleep(9000);
  tornado.castSpell(nullptr); // Yes LAST CD is over

  tornado.castSpell(nullptr); // current CD is 5
  sleep(5100);
  tornado.learnSpell(nullptr); //
  tornado.castSpell(nullptr);
  sleep(2000);
  tornado.castSpell(nullptr);
  return 0;
}
