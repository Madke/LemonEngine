// Standard Includes
#include <string>
#include <vector>

// Local Includes
#include "application.h"

using std::vector;
using std::string;

typedef int (*inputCallback)(void);

int main(int argc, char **argv) {
  vector<string> params;

  for (int i = 0; i < argc; i++) {
    params.push_back(argv[i]);
  }

  application app(params);

  while (app.loop()) {
    app.processEvents();
  }

  return app.exitStatus();
}
