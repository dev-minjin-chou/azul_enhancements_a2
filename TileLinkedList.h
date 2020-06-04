#ifndef TILE_LINKED_LIST
#define TILE_LINKED_LIST

#include "Tile.h"

class Node {
 public:
  Node(TilePtr value, Node *next, Node *prev);
  ~Node();

  TilePtr value;
  Node *next;
  Node *prev;
};

class TileLinkedList {
 public:
  TileLinkedList();
  ~TileLinkedList();

  // Get the size of the Linked List.
  unsigned int Size();
  // return the colour of the first tile in the linked list, throws run time
  // exception if linked list is empty
  Colour GetColour();
  // Add the tile to the back of the Linked List
  void AddTile(TilePtr t);
  // Remove the tile at the front of the Linked List
  TilePtr RemoveFront();
  // Remove the tile at the back of the Linked List
  TilePtr RemoveBack();
  // Removes all tiles from the Linked List
  void Clear();
  // read tiles into string
  std::string ToString();
  // To string for background coloured mosaic.
  std::string backgroundToString();
  // Tostring for saving files.
  std::string ToSaveString();
  // read tiles from string into a New TileLinkedList
  static std::shared_ptr<TileLinkedList> FromString(std::string str);

 private:
  Node *head;
  Node *tail;
  int count;
};

typedef std::shared_ptr<TileLinkedList> TileLinkedListPtr;

#endif  // TILE_LINKED_LIST