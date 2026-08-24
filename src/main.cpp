#include <iostream>
#include <fstream>

#include "dai_controller.hpp"

int main(int argc, char* argv[]) {  

  // check video device number and accept if it exists
  if (argc != 2) {
    std::cout << "Missing video device input\n";
    return 1;
  }
  
  char fname[32]; //writing fname this way to minimize compute and for own practice
  snprintf(fname, sizeof(fname), "/dev/video%s", argv[1]);

  //check if file exists
  std::ifstream f(fname);
  if (!f.good()) {
    std::cout << "Video device file not found\n";
    return 1;
  }
  f.close();
  
  std::cout << fname <<" found\n";
  
  // open write copy of the file
  std::ofstream dest(fname, std::ios::binary);

  // open dai camera and create dai stream
  dai_run(fname);

  char cmd[256];
  snprintf(cmd, sizeof cmd, "/usr/bin/v4l2loopback-ctl delete %s", fname);
  std::system(cmd);
  return 0;
}
