// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#include "GameCommand.h"

#include <sstream>

GameCommand::GameCommand(std::string savename)
    : cmd(commandtype::save), savename(savename) {}

GameCommand::GameCommand(int factory, Colour c, int row)
    : cmd(commandtype::turn) {
  std::get<0>(this->turn) = factory;
  std::get<1>(this->turn) = c;
  std::get<2>(this->turn) = row - 1;
}

void check_commandtype(GameCommand* cmd, commandtype type) {
  if (cmd->cmd != type) {
    std::stringstream e;
    e << "forbidden property for commandtype ";
    e << type;
    throw std::runtime_error(e.str());
  }
}

std::string GameCommand::GetSavename() {
  check_commandtype(this, commandtype::save);
  return this->savename;
}

Turn GameCommand::get_turn() {
  check_commandtype(this, commandtype::turn);
  return this->turn;
}