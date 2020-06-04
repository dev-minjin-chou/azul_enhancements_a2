#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "Tile.h"
#include "TileLinkedList.h"

// TESTING CLASS FOR LINKED LIST AND VECTOR WILL DELETE AFTER.
TileLinkedList* list = new TileLinkedList();
std::vector<Tile*> tiles;

Tile* new1 = new Tile(R);
Tile* new2 = new Tile(B);
Tile* new3 = new Tile(Y);
Tile* new4 = new Tile(L);
Tile* new5 = new Tile(U);
Tile* new6 = new Tile(R);

std::unique_ptr<Tile> tptr = std::make_unique<Tile>(R);

// Tile* getTile(int i);
void ShuffleTiles(int seed);
int main(void) {
  tiles.push_back(new1);
  tiles.push_back(new2);
  tiles.push_back(new3);
  tiles.push_back(new4);
  tiles.push_back(new5);
  tiles.push_back(new6);

  TilePtr t1 = std::make_unique<Tile>(R);
  TilePtr t2 = std::make_unique<Tile>(Y);
  TilePtr t3 = std::make_unique<Tile>(B);
  TilePtr t4 = std::make_unique<Tile>(U);
  list->AddTile(std::move(t1));
  list->AddTile(std::move(t2));
  list->AddTile(std::move(t3));
  list->AddTile(std::move(t4));

  // list->AddTile(new2);
  // list->AddTile(new3);
  // list->AddTile(new4);
  // list->RemoveBack();
  // list->RemoveFront();
  // list->Clear();

  for (int i = 0; i < tiles.size(); i++) {
    // ShuffleTiles(5);
    std::cout << tiles[i]->ToString();
  }
  std::cout << std::endl;
  std::cout << list->ToSaveString();
  // // std::cout << "front is: " << list->getFront()->ToString() << std::endl;
  // std::cout << "size is: " << list->Size() << std::endl;

  return EXIT_SUCCESS;
}

// Shuffle tiles randomly.
// void ShuffleTiles(int seed) { std::shuffle(tiles.begin(), tiles.end(),
// std::default_random_engine(seed)); }

//  Tile* getTile(int i)
//  {
//     Tile* g = nullptr;
//    for (unsigned int j = 0; j <= i; j++)
//    {
//      g = list->getTiles(j);
//      return g;
//    }
//  }
