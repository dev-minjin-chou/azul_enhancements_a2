#ifndef GAME_SAVER
#define GAME_SAVER
#define TF_SZ 6
#define P_SZ 2

#include <fstream>
#include <string>

#include "Game.h"
#include "GameLoader.h"

typedef std::shared_ptr<TileBag> TbagPtr;
typedef std::shared_ptr<BoxLid> BoxLidPtr;

class GameSaver {
 public:
  GameSaver(std::string savename, Players* players, Game* game, TbagPtr tilebag,
            BoxLidPtr boxlid, TileFactories* factories);

 private:
  const static char* savefilename[];
  std::string savename = "";
  std::string SaveFile(savefile filename);
  void SavePlayers(Players* players, Game* game);
  void SaveMosiac(Players* players);
  void SaveTileBagBoxLid(TbagPtr tilebag, BoxLidPtr boxlid);
  void SaveFactories(TileFactories* factories);
};

#endif  // GAME_SAVER