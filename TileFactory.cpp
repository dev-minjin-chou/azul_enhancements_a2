#include "TileFactory.h"

#include <iostream>
#include <sstream>

#include "Tile.h"
#include "TileLinkedList.h"

TileFactory::TileFactory() : colours(std::array<TileLinkedListPtr, TILE_SZ>()) {
  for (size_t i = 0; i < TILE_SZ; i++) {
    colours.at(i) = std::make_shared<TileLinkedList>();
  }
}

TileFactory::~TileFactory() {}

void PopulateFromTileBag(TileBag *tileBag) {}

void TileFactory::AddTile(TilePtr tile) {
  this->colours[tile->GetColour()]->AddTile(std::move(tile));
}

TileLinkedListPtr TileFactory::GetColour(Colour colour) {
  return this->colours[colour];
}

void TileFactory::SetColour(Colour colour, TileLinkedListPtr list) {
  this->colours[colour] = list;
}

unsigned int TileFactory::Size() {
  unsigned int size = 0;
  for (size_t i = 0; i < TILE_SZ; i++) {
    size += this->colours.at(i)->Size();
  }
  return size;
}

std::string TileFactory::ToString() {
  std::stringstream ss;
  for (size_t i = 0; i < TILE_SZ; i++) {
    if (this->colours.at(i)->Size() > 0) ss << this->colours.at(i)->ToString();
  }
  return ss.str();
}

std::string TileFactory::ToSaveString() {
  std::string rString;
  for (size_t i = 0; i < TILE_SZ; i++) {
    if (this->colours.at(i)->Size() > 0) {
      rString.append(this->colours.at(i)->ToSaveString());
    }
  }
  return rString;
}

TileFactoryPtr TileFactory::FromString(std::string line, int tll_index) {
  TileFactoryPtr tf = std::make_shared<TileFactory>();
  for (size_t i = 0; i < line.size(); i++) {
    TilePtr t = Tile::FromChar(line.at(i));
    tf->AddTile(std::move(t));
  }
  return tf;
}
