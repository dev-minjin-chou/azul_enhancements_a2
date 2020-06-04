// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#include "Game.h"

#include <iostream>
#include <sstream>

#include "GameSaver.h"
#include "Mosaic.h"

// test if player copy or move constructors are called
Game::Game(TileFactories&& factories, Players&& players,
           std::shared_ptr<TileBag>&& tilebag, std::shared_ptr<BoxLid>&& boxlid,
           int&& turn_index)
    : factories(std::move(factories)),
      players(std::move(players)),
      tbag(std::move(tilebag)),
      box_lid(std::move(boxlid)),
      turn_index(std::move(turn_index)){};

Game::~Game(){
    // arrays should self delete, elements in arrays should self delete
};

std::string Game::FactoriesToString() {
  std::stringstream ss;
  ss << "Factories: " << std::endl;
  for (size_t i = 0; i < TF_SZ; i++) {
    ss << i << ": ";
    ss << this->factories.at(i)->ToString() << std::endl;
  }
  return ss.str();
}

std::shared_ptr<Player> Game::GetCurrentPlayer() {
  return this->players.at(this->turn_index);
}

void Game::IterateTurnIndex() {
  this->turn_index = (this->turn_index + 1) % this->players.size();
}

void Game::PopulateTiles() {
  // Field for First player tile here

  // Loop through 5 factories.
  for (int i = 1; i < TF_SZ && tbag->Size() > E_TY; i++) {
    // Make sure that it doesn ppopulate 5 tiles in a single factory.
    for (int j = 0; j < MX_T && tbag->Size() > E_TY; j++) {
      // add a tile to the current factory
      factories.at(i)->AddTile(tbag->PopTile());
      // if the tbag is empty and boxlid has tiles, refill tilebag from boxlid
      if (tbag->Size() == E_TY && box_lid->Size() != E_TY) {
        tbag->AddTiles(box_lid->RemoveFrontTiles());
      }
    }
  }
  // add first player tile to centre factory
  this->factories.at(CENTRE_FACTORY)->AddTile(std::make_unique<Tile>(Colour::F));
}

bool Game::GameOver() {
  bool gameover = false;
  for (size_t i = 0; i < P_SZ; i++) {
    if (this->players.at(i)->GetMosaic()->RowFull()) {
      gameover = true;
    }
  }
  return gameover;
}

bool Game::RoundOver() {
  bool over = true;
  for (size_t i = 0; i < TF_SZ && over; i++) {
    if (this->factories.at(i)->Size() > 0) {
      over = false;
    }
  }

  return over;
}

bool Game::TryTurn(Turn turn, PlayerPtr player) {
  bool move_successful = true;
  try {
    int f = std::get<turnindex::factory>(turn);
    if (f < 0 || f >= TF_SZ)
      throw std::out_of_range("factory index out of range");
    Colour colour = std::get<turnindex::colour>(turn);
    if (colour < 0 || colour > TILE_SZ - 1)
      throw std::out_of_range("invalid colour");
    int pl = std::get<turnindex::pattern_line>(turn);
    if (pl < 0 || pl > MOSAIC_DIM)
      throw std::out_of_range("pattern line out of range");
    TileFactoryPtr factory = this->factories.at(f);
    TileLinkedListPtr colour_list = factory->GetColour(colour);
    if (colour_list->Size() < 1)
      throw std::runtime_error("colour not in factory");

    // TryMove will throw runtime_error before tiles are erroneously moved
    player->GetMosaic()->TryMove(colour, pl, colour_list);
    // move the first player tile to player's floor line if in factory
    if (factory->GetColour(Colour::F)->Size() > 0) {
      player->GetMosaic()->TryMove(Colour::F, FLOOR_INDEX,
                                   factory->GetColour(Colour::F));
      factory->SetColour(Colour::F, std::make_shared<TileLinkedList>());
    }
  } catch (std::exception& e) {
    std::cout << "Invalid move - " << e.what() << std::endl;
    move_successful = false;
  }
  return move_successful;
}

void Game::FactoryToCentre(unsigned int index) {
  // only move tiles from factory^index if factory is not centre factory
  if (index != CENTRE_FACTORY) {
    TileFactoryPtr tf = this->factories.at(index);
    for (size_t i = 0; i < TILE_SZ - 1; i++) {
      TileLinkedListPtr colour = tf->GetColour((Colour)i);
      while (colour->Size() > 0) {
        this->factories.at(CENTRE_FACTORY)->AddTile(colour->RemoveFront());
      }
    }
  }
}

void Game::Scoring() {
  // find pattern lines which are full
  for (size_t i = 0; i < P_SZ; i++) {
    PlayerPtr player = this->players.at(i);
    MosaicPtr mosaic = player->GetMosaic();
    int score = mosaic->PatternScore();
    int points = player->GetPoints() + score;
    TileLinkedListPtr floorline = player->GetMosaic()->GetFloorLine();
    int floor = mosaic->FloorPenalty();
    points = points - floor;
    if (points < 0) {
      player->SetPoints(0);
    } else {
      player->SetPoints(points);
    }

    // empty overflow into into boxlid FIFO
    TileLinkedListPtr overflow = mosaic->GetOverflow();
    while (overflow->Size() > 0)
      this->box_lid->StoreTiles(overflow->RemoveFront());
    // set player index to player who has first player tile
    if (mosaic->IsFirstPlayer()) {
      this->turn_index = i;
    }
  }
}

std::vector<PlayerPtr> Game::EndGameScoring() {
  std::vector<PlayerPtr> won = std::vector<PlayerPtr>();
  int highscore = 0;
  for (size_t i = 0; i < P_SZ; i++) {
    PlayerPtr player = this->players.at(i);
    int score = player->GetMosaic()->EndGameWallScore();
    int points = player->GetPoints() + score;
    player->SetPoints(points);
    if (points > highscore) {
      highscore = points;
      won.clear();
    }
    if (points == highscore) won.push_back(player);
  }
  return won;
}

unsigned int Game::getTurnIndex() { return this->turn_index; }

void Game::SaveGame(std::string savename) {
  GameSaver gs(savename, &players, this, tbag, box_lid, &factories);
}

std::string Game::ToString() {
  std::stringstream ss;
  ss << std::endl << "Game State: " << std::endl;
  ss << "TileBag: " << std::endl;
  ss << this->tbag->ToString() << std::endl;
  ss << "BoxLid: " << std::endl;
  ss << this->box_lid->ToString() << std::endl;
  ss << this->FactoriesToString();
  ss << "Players: " << std::endl;
  for (size_t i = 0; i < P_SZ; i++) {
    ss << this->players.at(i)->ToString();
  }
  ss << "turn_index: " << this->turn_index << std::endl;

  return ss.str();
}
