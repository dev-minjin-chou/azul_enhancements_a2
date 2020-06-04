#include "BoxLid.h"

BoxLid::BoxLid() { list = std::make_shared<TileLinkedList>(); }

BoxLid::BoxLid(BoxLid &&other) : list(std::move(other.list)) {}

BoxLid::~BoxLid() {}

void BoxLid::StoreTiles(TilePtr t) {
  while (t != nullptr) {
    list->AddTile(std::move(t));
  }
}

unsigned int BoxLid::Size() { return list->Size(); }

TilePtr BoxLid::RemoveFrontTiles() { return list->RemoveFront(); }

std::string BoxLid::ToString() { return list->ToString(); }

std::string BoxLid::ToSaveString() { return list->ToSaveString(); }

std::shared_ptr<BoxLid> BoxLid::FromString(const std::string line) {
  std::shared_ptr<BoxLid> box_lid = std::make_shared<BoxLid>();
  for (size_t i = 0; i < line.size(); i++) {
    box_lid->StoreTiles(Tile::FromChar(line[i]));
  }
  return box_lid;
}