// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef _GAMELOADER_H_
#define _GAMELOADER_H_

#include <string>

#include "Game.h"

enum savefile { factories = 0, mosaic = 1, players = 2, tilebag_boxlid = 3 };

class GameLoader {
 public:
  GameLoader(std::string savename);
  GamePtr LoadGame();

  const static char *savefilename[];

 private:
  void LoadTileBagBoxLid();
  void LoadFactories();
  void LoadMosaics();
  void LoadPlayers();
  std::ifstream OpenFile(savefile filename);
  std::string savename = "";
  bool alreadyLoaded = false;
  int turn_index = 0;
  std::shared_ptr<TileBag> tilebag = nullptr;
  std::shared_ptr<BoxLid> boxlid = nullptr;
  TileFactories factories;
  std::array<MosaicPtr, P_SZ> mosaics;
  Players players;
};

#endif