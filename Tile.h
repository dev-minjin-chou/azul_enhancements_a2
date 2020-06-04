// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef TILE_H_
#define TILE_H_

#include <memory>
#include <string>

#define EMPTY '.'
#define TILE_SZ 6

// ANSI COLOR CODES
#define RESET      "\u001b[0m"
#define FTC        "\u001b[95m"
#define RED        "\u001b[31m"
#define YELLOW     "\u001b[33m"
#define DARKBLUE   "\u001b[34m"
#define LIGHTBLUE  "\u001b[96m"
#define BLACK      "\u001b[90m"
#define FTILE      "\u0197"

// ANSI COLOR CODES FOR BACKGROUND.
#define RBG        "\u001b[30;41m"
#define YBG        "\u001b[30;43m"
#define DBG        "\u001b[30;44m"
#define LBG        "\u001b[30;106m"
#define BBG        "\u001b[40m"

using std::string;

enum Colour {
  R = 0,  // RED
  Y = 1,  // YELLOW
  B = 2,  // DARK BLUE
  L = 3,  // LIGHT BLUE
  U = 4,  // BLACK
  F = 5,  // FIRST PLAYER TO TAKE TILES FROM CENTRE FACTORY FOR THE ROUND
};

class Tile {
 public:
  // Constructor/Desctructor.
  Tile(Colour colour);
  Tile(Tile&& tile);
  ~Tile();

  // create a tile read from a character
  static std::unique_ptr<Tile> FromChar(char c);
  static Colour colourFromString(std::string str);

  std::string ToString();

  // ToString for coloured tiles.
  std::string colourToString();

  // ToString for coloured tiles background/
  std::string colouredBGToString();

  Colour GetColour();

 private:
  Colour colour;
  static const std::string colourStr[];
};

typedef std::unique_ptr<Tile> TilePtr;

#endif  // TILES_H_
