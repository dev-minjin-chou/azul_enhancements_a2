// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef USERPROMPT_H__
#define USERPROMPT_H__

#include <string>

#include "GameCommand.h"
#include "Tile.h"

class UserPrompt {
 public:
  static int Integer(int start, int end);
  static std::string name();

  // return a GameCommand, return nullptr if user has input ^D
  static GameCommand* NewGameCommand();
};

#endif  // USERPROMPT_H__
