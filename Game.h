// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef GAME_H_
#define GAME_H_
#define TF1_SZ 6
#define TF2_SZ 8
#define TF3_SZ 10
#define P_SZ 2
#define TP_SZ 3
#define MP_SZ 4
#define E_TY 0
#define MX_T 4
#define CENTRE_FACTORY 0
#define SECOND_FACTORY 1

#include <array>

#include "BoxLid.h"
#include "GameCommand.h"
#include "Player.h"
#include "TileBag.h"
#include "TileFactory.h"

typedef std::vector<TileFactoryPtr> TileFactories;
typedef std::vector<PlayerPtr> Players;

class Game {
 public:
  Game(TileFactories&& factories, Players&& players,
       std::shared_ptr<TileBag>&& tilebag, std::shared_ptr<BoxLid>&& boxlid,
       int&& turn_index);
  ~Game();

  // get the next player in the player array, loops back around
  PlayerPtr GetCurrentPlayer();

  // populate the factory with tiles from the tilebag
  void PopulateTiles();

  // Populate tiles for single centre factories mode.
  void FactoryOne();

  // Populate tiles for single centre factories mode.
  void FactorySecond();

  // move all tiles from factory to centre factory
  void FactoryToCentre(unsigned int index, unsigned int choice);

  // return true if a player's mosaic wall has a full row, otherwise return
  // false
  bool GameOver();

  // return true if all tile factories are empty, otherwise return false
  bool RoundOver();

  // get score for each pattern line, move filled pattern lines to wall,
  // delete first player tile
  void Scoring();

  // end of game Scoring, return vector of players who won
  std::vector<PlayerPtr> EndGameScoring();

  // get the turn index of the player
  unsigned int getTurnIndex();

  // get next turn_index
  void IterateTurnIndex();

  // save the game
  void SaveGame(std::string savename);

  //   try a player's move, if valid move, carry out tile move operations and
  //   return true, otherwise do not do anything and return false
  bool TryTurn(Turn turn, PlayerPtr player);

  std::string ToString();
  std::string FactoriesToString();

 private:
  TileFactories factories;
  Players players;
  std::shared_ptr<TileBag> tbag;
  std::shared_ptr<BoxLid> box_lid;
  unsigned int turn_index;
};

typedef std::shared_ptr<Game> GamePtr;

#endif  // GAME_H_
