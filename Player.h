// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "Mosaic.h"

typedef std::shared_ptr<Mosaic> MosaicPtr;

class Player {
 public:
  Player();
  Player(std::string name, int points, MosaicPtr&& mosaic);
  Player(std::string name, int points);
  Player(Player&& other);
  ~Player();

  std::string GetName();

  int GetPoints();
  void SetPoints(int points);

  MosaicPtr GetMosaic();

  std::string ToString();

 private:
  std::string name;
  int points;
  MosaicPtr mosaic;
};

typedef std::shared_ptr<Player> PlayerPtr;

#endif  // PLAYER_H_
