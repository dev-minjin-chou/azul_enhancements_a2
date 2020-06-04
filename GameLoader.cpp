// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#include "GameLoader.h"

#include <fstream>
#include <iostream>

GameLoader::GameLoader(std::string savename)
    : savename(savename),
      factories(TileFactories()),
      mosaics(std::array<MosaicPtr, P_SZ>()),
      players(Players()) {}

const char* GameLoader::savefilename[] = {"factories", "mosaic", "players",
                                          "tilebag_boxlid"};

std::ifstream GameLoader::OpenFile(savefile filename) {
  std::string savefilepath = this->savename + "-";
  savefilepath.append(GameLoader::savefilename[filename]);
  savefilepath.append(".save");
  std::ifstream in(savefilepath);
  return in;
}

GamePtr GameLoader::LoadGame() {
  if (this->alreadyLoaded) {
    throw std::runtime_error("Game already loaded");
  } else {
    this->LoadTileBagBoxLid();
    this->LoadFactories();
    this->LoadMosaics();
    this->LoadPlayers();
    this->alreadyLoaded = true;
    GamePtr game = std::make_shared<Game>(
        std::move(this->factories), std::move(this->players),
        std::move(this->tilebag), std::move(this->boxlid),
        std::move(this->turn_index));
    return game;
  }
}

void GameLoader::LoadFactories() {
  std::ifstream in = this->OpenFile(savefile::factories);
  for (size_t i = 0; i < TF_SZ; i++) {
    std::string line;
    if (!in.good()) throw std::runtime_error("factory unreadable");
    std::getline(in, line);
    this->factories.at(i) = TileFactory::FromString(line, i);
  }
  in.close();
}

void GameLoader::LoadMosaics() {
  std::ifstream in = this->OpenFile(savefile::mosaic);
  for (size_t p_i = 0; p_i < P_SZ; p_i++) {
    PatternLines pattern_lines = Mosaic::InitPatternLines();
    for (size_t ptn_i = 0; ptn_i < MOSAIC_DIM; ptn_i++) {
      std::string p_line;
      if (!in.good()) throw std::runtime_error("patternline unreadable");
      std::getline(in, p_line);
      pattern_lines.at(ptn_i) = TileLinkedList::FromString(p_line);
    }

    Wall wall = Mosaic::InitWall();
    for (unsigned int row = 0; row < wall.size(); ++row) {
      std::string row_str;
      if (!in.good()) throw std::runtime_error("wall unreadable");
      std::getline(in, row_str);
      for (size_t col = 0; col < wall.at(row).size(); col++) {
        if (row_str.at(col) != EMPTY) {
          wall.at(row).at(col) = Tile::FromChar(row_str.at(col));
        }
      }
    }

    std::string f_line;
    if (!in.good()) throw std::runtime_error("patternline unreadable");
    std::getline(in, f_line);
    FloorLinePtr floor_line = TileLinkedList::FromString(f_line);
    this->mosaics.at(p_i) = std::make_shared<Mosaic>(
        std::move(wall), std::move(pattern_lines), std::move(floor_line));
  }
  in.close();
}

void GameLoader::LoadPlayers() {
  std::ifstream in = this->OpenFile(savefile::players);
  // read in current player index
  string ti_str;
  if (!in.good()) throw std::runtime_error("turn_index unreadable");
  std::getline(in, ti_str);
  this->turn_index = std::stoi(ti_str);
  for (size_t i = 0; i < P_SZ; i++) {
    std::string name;
    if (!in.good()) throw std::runtime_error("player name unreadable");
    std::getline(in, name);
    std::string p_str;
    if (!in.good()) throw std::runtime_error("player points unreadable");
    std::getline(in, p_str);
    int points = std::stoi(p_str);
    MosaicPtr mosaic = std::move(this->mosaics.at(i));
    this->players.at(i) =
        std::make_shared<Player>(name, points, std::move(mosaic));
  }
  in.close();
}

void GameLoader::LoadTileBagBoxLid() {
  std::ifstream in = this->OpenFile(savefile::tilebag_boxlid);
  std::string tb_line;
  if (!in.good()) throw std::runtime_error("tilebag unreadable");
  std::getline(in, tb_line);
  this->tilebag = TileBag::FromString(tb_line);
  std::string bl_line;
  if (!in.good()) throw std::runtime_error("boxlid unreadable");
  std::getline(in, bl_line);
  this->boxlid = BoxLid::FromString(bl_line);
  in.close();
}