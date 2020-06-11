// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef GAMECOMMAND_H_
#define GAMECOMMAND_H_

#include <string>
#include <utility>

#include "Tile.h"

typedef std::tuple<int, Colour, int> Turn;

enum commandtype {turn, save};

enum turnindex { factory, colour, pattern_line };

class GameCommand {
 public:
  GameCommand(std::string savename);
  GameCommand(int factory, Colour c, int row);

  commandtype cmd;
  std::string GetSavename();
  Turn get_turn();

 private:
  std::string savename;
  Turn turn;
};

#endif  // GAMECOMMAND_H_