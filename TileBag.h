// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef TILEBAG_H_
#define TILEBAG_H_
#include <random>
#include <vector>

#include "Tile.h"

#define COLOUR_SZ 20

class TileBag {
 public:
  //  default constructor for arrays
  TileBag();
  TileBag(TileBag&& other);
  ~TileBag();

  // initialise tilebag with new set of tiles
  void NewGame(unsigned int seed);

  // The size of the vector.
  unsigned int Size();
  // Adding tiles into tiles bag.
  void AddTiles(TilePtr t);
  // pop tile from the top of the vector.
  TilePtr PopTile();
  // Clear Tile Bag.
  void Clear();
  // create string from tiles in tilebag
  std::string ToString();
  // Shuffle tiles randomly.
  void ShuffleTiles(unsigned int seed);

  // get TileBag from string
  static std::shared_ptr<TileBag> FromString(std::string line);

 private:
  // Tiles vector to store tiles in the bag.
  std::vector<TilePtr> tiles;
};

#endif  // TILEBAG_H_
