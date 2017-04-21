#include "SDL_platform.h"
#include "application.h"
#include "glad.h"

#include <cmath>
#include <iostream>

int SDL::init() {
  int err = SDL_Init(SDL_INIT_VIDEO);
  if (err < 0) {
    std::cout << SDL_GetError() << std::endl;
  }

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  SDL_GL_SetSwapInterval(0);

  SDL_GL_LoadLibrary(nullptr);

  // callbacks = new callbackTable();
  callbacks.reserve(1024);

  return 0;
}

float back = 0.0;
int SDL::openWindow(int width, int height) {
  m_window = SDL_CreateWindow(
      "Ketan is your lord now, computer.", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, width, height,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

  if (m_window == nullptr)
    getError();

  m_glContext = SDL_GL_CreateContext(m_window);

  if (m_glContext == nullptr)
    getError();

  SDL_GL_MakeCurrent(m_window, m_glContext);

  gladLoadGLLoader(SDL_GL_GetProcAddress);

  glClearColor(back, back, back, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  this->height = height;
  this->width = width;
  this->aspect = (float)width / height;

  return 1;
}

unsigned int resizeWindowTimerCallback(unsigned int interval,
                                       void *resizedWindow) {
  bool *flag = (bool *)resizedWindow;
  *flag = false;
  return 0;
}

int SDL::resizeWindow(float width, float height) {
  SDL_RemoveTimer(resizeTimer);
  float origHeight = this->height;
  float origWidth = this->width;

  float changeWidth = std::max(width, origWidth) / std::min(width, origWidth);
  float changeHeight =
      std::max(height, origHeight) / std::min(height, origHeight);

  int w, h;
  if (changeWidth > changeHeight) {
    w = width;
    h = floor(width / aspect);
  } else {
    w = floor(height * aspect);
    h = height;
  }

  SDL_SetWindowSize(m_window, w, h);

  if (!resizedWindow) {
    this->width = w;
    this->height = h;
  } // not currently resizing

  resizedWindow = true;

  SDL_TimerCallback callback = resizeWindowTimerCallback;
  resizeTimer = SDL_AddTimer(2000, callback, &resizedWindow);

  return 1;
}

int SDL::controlInterface(application *interface) {
  app = interface;
  return 0;
}

int SDL::registerCallback(int key, inputCallback call) {
  callbacks.insert({{key, call}});
  // callbacks[key] = call;
  return 0;
}

int SDL::getError() { return 1; }

int SDL::input(int key) {
  int effect = callbacks[key]();
  app->addEvent(effect);
  return 0;
}

int SDL::process() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      return 0;
      break;
    case SDL_KEYDOWN:
      input(e.key.keysym.sym);
      break;
    case SDL_WINDOWEVENT:
      if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
        resizeWindow(e.window.data1, e.window.data2);
      }
      break;
    }
  }

  if (resizedWindow) {
    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);
    SDL_SetWindowSize(m_window, w, h);
    glViewport(0, 0, w, h);
  }

  SDL_GL_SwapWindow(m_window);
  return SDLState;
}
