// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef MENU_H_
#define MENU_H_

#include <string>

#include "Game.h"
#include "GameLoader.h"
#include "Menu.h"
#include "TileFactory.h"

class Controller {
 public:
  Controller(int seed);
  void MainMenu();

 private:
  void NewGame();
  void LoadGame();
  void Credits();

  // while player has not made a valid command, read in player's input
  // if it is a turn, try it in the game, if it is save command, save the game
  // returns boolean representing whether user pressed ^D or not
  bool PlayerTurn(GamePtr game, PlayerPtr player);

  // play a game until it is gameOver, or ^D received
  void Play(GamePtr game);

  // create a new player named according to user input
  PlayerPtr NewPlayer(int p_count);
  int seed;
};

#endif  // MENU_H_
