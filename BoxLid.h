// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef ASS_TWO_BOXLID
#define ASS_TWO_BOXLID

#include <string>

#include "TileLinkedList.h"

class BoxLid {
 public:
  // Constructor/Deconstructor
  BoxLid();
  BoxLid(BoxLid &&other);
  ~BoxLid();

  // Storing tiles from mosiac to the linked list.
  void StoreTiles(TilePtr t);
  // Get the size of the box lid linked list.
  unsigned int Size();
  // Remove tiles from front of the lid.
  TilePtr RemoveFrontTiles();
  // create string from tiles in box lid.
  std::string ToString();
  // toString for saving files.
  std::string ToSaveString();
  // read tiles from string into a new BoxLid
  static std::shared_ptr<BoxLid> FromString(std::string line);

 private:
  std::shared_ptr<TileLinkedList> list;
};

#endif  // ASS_TWO_BOXLID