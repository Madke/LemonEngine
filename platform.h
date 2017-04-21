#ifndef PLATFORM_H
#define PLATFORM_H

typedef int (*inputCallback)(void);

class application;

class platform {
public:
  platform() {}
  ~platform() {}

  virtual int init() { return 0; }

  virtual int openWindow(int, int) { return 0; }
  virtual int resizeWindow(float, float) { return 0; }

  virtual int controlInterface(application *) { return 0; }
  virtual int registerCallback(int, inputCallback) { return 0; }

  virtual int getError() { return 0; }

  virtual int process() { return 0; }
};

#endif
