#ifndef SDL_PLATFORM_H
#define SDL_PLATFORM_H

#include "SDL2/SDL.h"
#include "platform.h"

#include <unordered_map>

typedef std::unordered_map<int, inputCallback> callbackTable;
typedef SDL_Window Window;
typedef SDL_Renderer Renderer;
typedef SDL_Surface Surface;
typedef SDL_GLContext GLContext;

class SDL : public platform {
private:
  int height;
  int width;
  float aspect;

  application *app;

  Window *m_window;
  Renderer *m_renderer;
  Surface *m_screenSurface;
  GLContext m_glContext;

  callbackTable callbacks;

  int SDLState = 1;

  bool resizedWindow;
  SDL_TimerID resizeTimer;

public:
  SDL() : platform() {}
  ~SDL() {}

  int init();

  int openWindow(int, int);
  int resizeWindow(float, float);

  int controlInterface(application *);
  int registerCallback(int, inputCallback);

  int getError();

  int input(int);
  int process();
};

#endif
