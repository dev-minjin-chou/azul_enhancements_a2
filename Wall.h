// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef WALL_H_
#define WALL_H_

#define WALL_SIZE 5

#include "Tile.h"

class Wall {
 public:
  Wall();

 private:
  Tile tiles[WALL_SIZE][WALL_SIZE];
};

#endif  // WALL_H_
