#include "TileLinkedList.h"

#include <iostream>
#include <sstream>

#include "Tile.h"

Node::Node(TilePtr value, Node* next, Node* prev)
    : value(std::move(value)), next(next), prev(prev) {}

Node::~Node() {
  if (this->value != nullptr) {
    this->value = nullptr;
  }
}

TileLinkedList::TileLinkedList() : head(nullptr), tail(nullptr), count(0) {}

TileLinkedList::~TileLinkedList() { Clear(); }

unsigned int TileLinkedList::Size() { return count; }

Colour TileLinkedList::GetColour() {
  if (this->head == nullptr)
    throw std::runtime_error("TileLinkedList is empty");
  return this->head->value->GetColour();
}

// add to back of linked list
void TileLinkedList::AddTile(TilePtr tile) {
  if (tile == nullptr) throw std::runtime_error("tile is a nullptr");
  Node* addNode = new Node(std::move(tile), nullptr, nullptr);

  if (this->head == nullptr) {
    head = addNode;
    tail = addNode;
  } else {
    this->tail->next = addNode;
    addNode->prev = this->tail;
    this->tail = addNode;
  }
  ++count;
}

TilePtr TileLinkedList::RemoveFront() {
  if (this->head == nullptr)
    throw std::runtime_error("TileLinkedList is empty");
  TilePtr remove_front = std::move(this->head->value);
  this->head->value = nullptr;
  if (this->head->next != nullptr) {
    this->head = this->head->next;
    delete this->head->prev;
    this->head->prev = nullptr;
  } else {
    delete this->head;
    this->head = nullptr;
    this->tail = nullptr;
  }
  --this->count;
  return remove_front;
}

TilePtr TileLinkedList::RemoveBack() {
  if (this->tail == nullptr)
    throw std::runtime_error("TileLinkedList is empty");
  TilePtr remove_back = std::move(this->tail->value);
  this->tail->value = nullptr;
  if (this->tail->prev != nullptr) {
    this->tail = this->tail->prev;
    delete this->tail->next;
    this->tail->next = nullptr;
  } else {
    delete this->tail;
    this->head = nullptr;
    this->tail = nullptr;
  }
  --this->count;
  return remove_back;
}

void TileLinkedList::Clear() {
  while (head != nullptr) {
    RemoveFront();
  }
}

std::string TileLinkedList::ToString() {
  std::stringstream ss;
  Node* n = head;
  while (n != nullptr && n->value != nullptr) {
    ss << n->value->colourToString() << " ";
    n = n->next;
  }
  return ss.str();
}

std::string TileLinkedList::backgroundToString() {
  std::stringstream st;
  Node* h = head;
  while (h != nullptr && h->value != nullptr) {
    st << h->value->colouredBGToString() << " ";
    h = h->next;
  }
  return st.str();
}

std::string TileLinkedList::ToSaveString() {
  std::string rString;
  Node* a = head;
  while (a != nullptr && a->value != nullptr) {
    rString.append(a->value->ToString());
    a = a->next;
  }
  return rString;
}

TileLinkedListPtr TileLinkedList::FromString(std::string line) {
  TileLinkedListPtr tl = std::make_shared<TileLinkedList>();
  for (size_t i = 0; i < line.size(); i++) {
    if (line.at(i) != EMPTY) {
      TilePtr t = Tile::FromChar(line.at(i));
      tl->AddTile(std::move(t));
    }
  }
  return tl;
}