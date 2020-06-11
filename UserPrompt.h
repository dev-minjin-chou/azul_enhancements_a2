// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef USERPROMPT_H__
#define USERPROMPT_H__

#define MIN_PSZ 2
#define MAX_PSZ 4

#include <string>

#include "GameCommand.h"
#include "Tile.h"

class UserPrompt {
 public:
  static int Integer(int start, int end);
  static std::string name();
  static unsigned int playerCount();
  static unsigned int centreF();

  // return a GameCommand, return nullptr if user has input ^D
  static GameCommand* NewGameCommand();
};

#endif  // USERPROMPT_H__
