#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

#include "SDL_platform.h"
#include "application.h"

int frameDeltaLog[6000];
int vertexSizeLog[6000];
int i = 0;

chrono::steady_clock::time_point now, start;
chrono::duration<int, milli> dt, target;

application::application(vector<string>) {
  state[STATE_Loop] = 1;
  state[STATE_FPS] = 60;
  state[STATE_MSPF] = 1000 / state[STATE_FPS];
  state[STATE_Width] = 640;
  state[STATE_Height] = 480;

  target = chrono::duration<int, milli>(state[STATE_MSPF]);

  ticks = steady_clock::now();
  start = ticks;

  PlatformInterface = new SDL();
  events = vector<int>();
  events.reserve(12 * sizeof(int));

  PlatformInterface->init();

  PlatformInterface->openWindow(state[STATE_Width], state[STATE_Height]);

  loadFiles(".");

  registerCallbacks();
}

application::~application() {}

int application::loadFiles(string path) {
  ifstream VertexShader;
  VertexShader.open("./vs.txt", ios::in);
  cout << VertexShader;
}

int application::loop() {
  vertexSizeLog[i] = 0;

  now = chrono::steady_clock::now();
  dt = chrono::duration_cast<milliseconds>(now - ticks);
  std::this_thread::sleep_for(target - dt);
  ticks = chrono::steady_clock::now();

  frameDeltaLog[i++] = (chrono::steady_clock::now() - start).count();
  if (i == 6000) {
    i = 0;
  }

  PlatformInterface->process();

  return state[STATE_Loop];
}

int application::exitStatus() {
  int start = (i == 5999) ? 0 : i + 1;
  for (i = start; i < 6000; i++) {
    std::cout << frameDeltaLog[i] << "," << vertexSizeLog[i] << std::endl;
  }
  if (start != 0) {
    for (i = 0; i < start; i++) {
      std::cout << frameDeltaLog[i] << "," << vertexSizeLog[i] << std::endl;
    }
  }
  return state[STATE_ExitStatus];
}
