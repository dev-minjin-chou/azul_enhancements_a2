// Copyright 2020 Chou, Dechathaweewat, Hollis-London

#include <fstream>
#include <iostream>
#include <sstream>

#include "Controller.h"

class Args {
 public:
  const int args_length = 3;
  const std::string seed_flag = "-s";
  const int seed_flag_index = 1;
  Args(int argc, char** argv);
  int seed;
  bool valid = true;
};

Args::Args(int argc, char** argv) {
  if (argc != args_length || argv[seed_flag_index] != seed_flag) {
    this->valid = false;
  } else {
    try {
      std::stringstream seed(argv[2]);
      seed >> this->seed;
    } catch (...) {
      this->valid = false;
    }
  }
  if (!this->valid) {
    std::cout << "Usage: \n " << argv[0] << " -s <seed>" << std::endl;
  }
}

int main(int argc, char** argv) {
  Args args(argc, argv);
  if (args.valid) {
    // Open a log file for output
    std::ofstream logfile("log.txt");
    Controller ctrl(args.seed);
    ctrl.MainMenu();
    logfile.close();
  }
}
