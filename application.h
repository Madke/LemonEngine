#ifndef APPLICATION_H
#define APPLICATION_H

#include <chrono>
#include <string>
#include <vector>

#include "platform.h"

using std::string;
using std::vector;
using namespace std::chrono;

enum stateVariable {
  STATE_Loop,
  STATE_ExitStatus,
  STATE_FPS,
  STATE_MSPF,
  STATE_Width,
  STATE_Height,
  STATE_Ticks,
  STATE_MAX = STATE_Ticks + 1
};

class application {
public:
  int state[STATE_MAX];

  vector<int> events;

  steady_clock::time_point ticks;
  platform *PlatformInterface;

  application(vector<string>);
  ~application();

  int loadFiles(string path);
  int registerCallbacks();
  int processEvents();
  int addEvent(int);
  int loop();
  int exitStatus();
};

#endif
