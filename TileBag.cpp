#include "TileBag.h"

#include <algorithm>
#include <fstream>
#include <random>
#include <sstream>

TileBag::TileBag() : tiles(std::vector<TilePtr>()) {}
TileBag::TileBag(TileBag&& other) : tiles(std::move(other.tiles)) {}
TileBag::~TileBag() {}

void TileBag::NewGame(unsigned int seed) {
  // iterate each colour except last colour (first player tile)
  // for each colour add 20 tiles to tilebag
  for (size_t i = 0; i <= Colour::U; i++) {
    for (size_t t = 0; t < COLOUR_SZ; t++) {
      this->tiles.push_back(std::make_unique<Tile>((Colour)i));
    }
  }
  this->ShuffleTiles(seed);
}

unsigned int TileBag::Size() { return this->tiles.size(); }

// Adding tiles into tiles bag.
void TileBag::AddTiles(TilePtr t) { this->tiles.push_back(std::move(t)); }

TilePtr TileBag::PopTile() {
  TilePtr tile = std::move(tiles.back());
  this->tiles.pop_back();
  return tile;
}

void TileBag::Clear() { tiles.clear(); }

// Shuffle tiles randomly.
void TileBag::ShuffleTiles(unsigned int seed) {
  std::shuffle(this->tiles.begin(), this->tiles.end(),
               std::default_random_engine(seed));
}

std::shared_ptr<TileBag> TileBag::FromString(const std::string line) {
  std::shared_ptr<TileBag> tbag = std::make_shared<TileBag>();
  for (size_t i = 0; i < line.size(); i++) {
    tbag->AddTiles(Tile::FromChar(line[i]));
  }
  return tbag;
}

std::string TileBag::ToString() {
  std::stringstream ss;
  for (size_t i = 0; i < this->Size(); i++) {
    ss << this->tiles.at(i)->ToString();
  }
  ss << std::endl;
  return ss.str();
}