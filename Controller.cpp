// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#include "Controller.h"

#include <iostream>

#include "Game.h"
#include "GameCommand.h"
#include "UserPrompt.h"

Controller::Controller(int seed) : seed(seed){};

enum mode { null, new_game, load_game, credits, help, quit };

void Controller::MainMenu() {
  std::cout << "seed: " << this->seed << std::endl;
  mode choice = mode::null;

  while (std::cin.good() && choice != mode::quit) {
    //   print menu
    Menu::Main();
    //   take user input
    choice = (mode)UserPrompt::Integer(mode::new_game, mode::quit);

    if (choice == mode::new_game) {
      this->NewGame();
    } else if (choice == mode::load_game) {
      this->LoadGame();
    } else if (choice == mode::credits) {
      Menu::Credits();
    } else if (choice == mode::help) {
      Menu::Instructions();
    }
    if (!std::cin.good()) {
      std::cout << "\nGoodbye" << std::endl;
    }
  }
}

PlayerPtr Controller::NewPlayer(int p_count) {
  std::cout << "Enter a name for player " << p_count << std::endl;
  std::string name = UserPrompt::name();
  std::cout << std::endl;
  return std::make_shared<Player>(name, 0);
}

void Controller::NewGame() {
  std::cout << "\nStarting a New Game\n" << std::endl;

  Players players = Players();
  for (size_t i = 0; i < P_SZ; i++) {
    players.at(i) = this->NewPlayer(i + 1);
  }
  TileFactories factories = TileFactories();
  for (size_t i = 0; i < TF_SZ; i++) {
    factories.at(i) = std::make_shared<TileFactory>();
  }
  std::shared_ptr<TileBag> tbag = std::make_shared<TileBag>();
  tbag->NewGame(this->seed);
  std::shared_ptr<BoxLid> box_lid = std::make_shared<BoxLid>();
  GamePtr game =
      std::make_shared<Game>(std::move(factories), std::move(players),
                             std::move(tbag), std::move(box_lid), 0);
  std::cout << std::endl << "Let's Play!" << std::endl << std::endl;
  std::cout << std::endl << "=== Start Round ===" << std::endl;
  game->PopulateTiles();
  this->Play(game);
}

void Controller::LoadGame() {
  std::cout << "Enter the savename from which to load a game" << std::endl;
  std::string save = UserPrompt::name();
  bool fail = false;
  GamePtr game = nullptr;
  try {
    game = GameLoader(save).LoadGame();
    std::cout << game->ToString() << std::endl;
  } catch (std::runtime_error& e) {
    std::cout << "Error opening gamesave - " << e.what() << std::endl;
    fail = true;
  }
  if (!fail) {
    this->Play(game);
  }
}

void Controller::Play(GamePtr game) {
  bool leave_program = false;
  do {
    // if tiles already in TileFactories, continue round
    do {
      PlayerPtr player = game->GetCurrentPlayer();
      std::cout << "TURN FOR PLAYER: " << player->GetName() << std::endl;
      std::cout << game->FactoriesToString() << std::endl;
      std::cout << player->ToString();
      leave_program = this->PlayerTurn(game, player);
    } while (!game->RoundOver() && !leave_program);
    if (!leave_program) {
      game->Scoring();
      if (!game->GameOver()) {
        // All TileFactories are empty, start new round
        std::cout << std::endl << "=== Start Round ===" << std::endl;
        game->PopulateTiles();
      }
    }
  } while (!game->GameOver() && !leave_program);
  if (!leave_program) {
    // game over
    std::vector<PlayerPtr> players = game->EndGameScoring();
    for (size_t i = 0; i < players.size(); i++) {
      std::cout << players.at(i)->GetName() << " wins!" << std::endl;
    }

    std::cout << "=== GAME OVER ===" << std::endl << std::endl;
    std::cout << "Enter name for savegame:" << std::endl;
    std::string name = UserPrompt::name();
    game->SaveGame(name);
    std::cout << game->ToString() << std::endl;
    std::cout << "Game saved." << std::endl;
  }
}

bool Controller::PlayerTurn(GamePtr game, PlayerPtr player) {
  bool turn_over = false;
  bool leave_program = false;
  while (!turn_over) {
    GameCommand* game_cmd = UserPrompt::NewGameCommand();
    if (game_cmd != nullptr) {
      if (game_cmd->cmd == commandtype::turn) {
        bool success = game->TryTurn(game_cmd->get_turn(), player);
        if (success) {
          std::cout << "Turn successful." << std::endl;
          int index = std::get<turnindex::factory>(game_cmd->get_turn());
          game->FactoryToCentre(index);
          game->IterateTurnIndex();
          turn_over = true;
        }
      } else if (game_cmd->cmd == commandtype::save) {
        game->SaveGame(game_cmd->GetSavename());
        std::cout << game->ToString() << std::endl;
        std::cout << "Game saved." << std::endl;
      } else {
        std::cout << "commandtype unrecognised" << std::endl;
      }
      delete game_cmd;
    } else {
      turn_over = true;
      leave_program = true;
    }
    std::cout << std::endl;
  }
  return leave_program;
}
