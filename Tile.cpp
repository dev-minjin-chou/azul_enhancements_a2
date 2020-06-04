#include "Tile.h"

#include <iostream>

Tile::Tile(Colour colour) : colour(colour) {}

Tile::Tile(Tile&& other) : colour(other.colour) {}

Tile::~Tile() { std::cout << "~" << this->ToString() << " "; }

const std::string Tile::colourStr[] = {"R", "Y", "B", "L", "U", "F"};

Colour Tile::GetColour() { return this->colour; }

std::string Tile::ToString() { 
   return colourStr[this->colour]; 
  }

std::string Tile::colourToString()
{
   std::string colorString;
  if (colourStr[this->colour] == "R")
  {
    colorString = RED;
    colorString.append(colourStr[this->colour]);
    colorString.append(RESET);
  } else if (colourStr[this->colour] == "Y") {
    colorString = YELLOW;
    colorString.append(colourStr[this->colour]);
    colorString.append(RESET);
  } else if (colourStr[this->colour] == "B") {
    colorString = DARKBLUE;
    colorString.append(colourStr[this->colour]);
    colorString.append(RESET);
  } else if (colourStr[this->colour] == "L") {
    colorString = LIGHTBLUE;
    colorString.append(colourStr[this->colour]);
    colorString.append(RESET);
  } else if (colourStr[this->colour] == "U") {
    colorString = BLACK;
    colorString.append(colourStr[this->colour]);
    colorString.append(RESET);
  } else {
    colorString = FTC;
    colorString.append(FTILE);
    colorString.append(RESET);
  }
  return colorString;
}

std::string Tile::colouredBGToString()
{
   std::string colorBG;
  if (colourStr[this->colour] == "R")
  {
    colorBG = RBG;
    colorBG.append(colourStr[this->colour]);
    colorBG.append(RESET);
  } else if (colourStr[this->colour] == "Y") {
    colorBG = YBG;
    colorBG.append(colourStr[this->colour]);
    colorBG.append(RESET);
  } else if (colourStr[this->colour] == "B") {
    colorBG = DBG;
    colorBG.append(colourStr[this->colour]);
    colorBG.append(RESET);
  } else if (colourStr[this->colour] == "L") {
    colorBG = LBG;
    colorBG.append(colourStr[this->colour]);
    colorBG.append(RESET);
  } else {
    colorBG = BBG;
    colorBG.append(colourStr[this->colour]);
    colorBG.append(RESET);
  }
  return colorBG;
}

std::unique_ptr<Tile> Tile::FromChar(char c) {
  Colour colour = Tile::colourFromString(std::string(1, c));
  return std::make_unique<Tile>(colour);
}

Colour Tile::colourFromString(std::string colour) {
  int i = 0;
  bool t = true;
  for (; i < TILE_SZ && t;) {
    if (colourStr[i] == colour) {
      t = false;
    } else {
      i++;
    }
  }
  if (t) {
    std::string e = colour + " is not a valid tile colour";
    throw std::runtime_error(e);
  }
  return (Colour)i;
}