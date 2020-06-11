#include "GameSaver.h"

#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::ofstream;
using std::string;

GameSaver::GameSaver(string savename, Players* players, Game* game,
                     TbagPtr tilebag, BoxLidPtr boxlid,
                     TileFactories* factories)
    : savename(savename) {
  SavePlayers(players, game);
  SaveMosiac(players);
  SaveTileBagBoxLid(tilebag, boxlid);
  SaveFactories(factories);
}

string GameSaver::SaveFile(savefile filename) {
  string openFile = this->savename + "-";
  openFile.append(GameLoader::savefilename[filename]);
  openFile.append(".save");
  return openFile;
}

void GameSaver::SavePlayers(Players* players, Game* game) {
  // Opens the players.save file
  ofstream out;
  try {
    out.open(SaveFile(savefile::players));
    if (out.is_open()) {
      if (out.good()) {
        out << game->getTurnIndex() << std::endl;
        for (size_t i = 0; i < players->size(); i++) {
          out << players->at(i)->GetName() << std::endl;
          out << players->at(i)->GetPoints() << std::endl;
        }
        out.close();
      } else {
        throw std::runtime_error("File is corrupted.");
      }
    } else {
      throw std::runtime_error("Unable to open file.");
    }
  } catch (...) {
    std::cerr << "Unexpected error occured.\n";
  }
}

void GameSaver::SaveMosiac(Players* players) {
  ofstream out;
  try {
    out.open(SaveFile(savefile::mosaic));
    if (out.is_open()) {
      if (out.good()) {
        for (size_t i = 0; i < players->size(); i++) {
          out << players->at(i)->GetMosaic()->PatternLinesToString();
          out << players->at(i)->GetMosaic()->WallToString();
          out << players->at(i)->GetMosaic()->FloorLineToString();
        }
        out.close();
      } else {
        throw std::runtime_error("File is corrupted.");
      }
    } else {
      throw std::runtime_error("Unable to open file.");
    }
  } catch (...) {
    std::cerr << "Unexpected error occured.\n";
  }
}

void GameSaver::SaveTileBagBoxLid(
    TbagPtr tilebag,
    BoxLidPtr boxlid)  // Can we use pointers? for the parameters
{
  ofstream out;
  try {
    out.open(SaveFile(savefile::tilebag_boxlid));
    if (out.is_open()) {
      if (out.good()) {
        // If tilebag and boxlid is not empty.
        out << tilebag->ToString();
        out << boxlid->ToSaveString();
        out.close();
      } else {
        throw std::runtime_error("File is corrupted.");
      }
    } else {
      throw std::runtime_error("Unable to open file.");
    }
  } catch (...) {
    std::cerr << "Unexpected error occured.\n";
  }
}

void GameSaver::SaveFactories(TileFactories* factories) {
  ofstream out;
  try {
    out.open(SaveFile(savefile::factories));
    if (out.is_open()) {
      if (out.good()) {
        for (unsigned int i = 0; i < factories->size(); i++) {
          out << factories->at(i)->ToSaveString() << std::endl;
        }
      } else {
        throw std::runtime_error("File is corrupted.");
      }
    } else {
      throw std::runtime_error("Unable to open file.");
    }
  } catch (...) {
    std::cerr << "Unexpected error occured.\n";
  }
}
