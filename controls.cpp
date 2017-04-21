#include "SDL2/SDL_keycode.h"
#include "application.h"

typedef int (*inputCallback)(void);

enum action { ACTION_EXIT };

int quit() { return ACTION_EXIT; }

int application::processEvents() {
  for (int i = 0; i < events.size(); i++) {
    switch (events[i]) {
    case ACTION_EXIT:
      state[STATE_Loop] = 0;
      break;
    default:
      break;
    }
  }
  events.clear();
  return 1;
}

int application::addEvent(int key) {
  events.push_back(key);
  return 0;
}

int application::registerCallbacks() {
  PlatformInterface->controlInterface(this);

  PlatformInterface->registerCallback(SDLK_ESCAPE, quit);
  return 1;
}
