// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef TILEFACTORIES_H_
#define TILEFACTORIES_H_
#include <array>
#include <string>

#include "Tile.h"
#include "TileBag.h"
#include "TileLinkedList.h"

class TileFactory {
 public:
  TileFactory();
  ~TileFactory();
  //
  bool isAllFactoryEmpty();

  void AddTile(TilePtr tile);
  // Return specific tile colour linkedlist
  TileLinkedList *GetTilesWithColour(int index, Colour colour);

  void PopulateFromTileBag(TileBag *tileBag);

  // get a specific TileLinkedList by Colour enum index
  TileLinkedListPtr GetColour(Colour colour);

  // set a colour's TileLinkedList to a new TileLinkedList, replacing the old.
  void SetColour(Colour colour, TileLinkedListPtr list);

  // get the accumulated size of all tiles in the tilefactory
  unsigned int Size();

  // create string from tiles in tilefactory
  std::string ToString();

  // ToString for saving tile factoires.
  std::string ToSaveString();
  // read tiles from string, take index to validate num of tiles in factory
  static std::shared_ptr<TileFactory> FromString(std::string line, int index);

 private:
  std::array<TileLinkedListPtr, TILE_SZ> colours;
};

typedef std::shared_ptr<TileFactory> TileFactoryPtr;

#endif  // TILEFACTORIES_H_
