// Copyright 2020 Chou, Dechathaweewat, Hollis-London
#ifndef MOSAIC_H_
#define MOSAIC_H_

#define MOSAIC_DIM 5
#define FLOOR_SZ 7
#define FLOOR_INDEX 5

#define ROW_FULL_BONUS 2
#define COL_FULL_BONUS 7
#define COMP_COLOUR_BONUS 10
#include <array>

#include "Tile.h"
#include "TileLinkedList.h"

typedef std::array<std::array<TilePtr, MOSAIC_DIM>, MOSAIC_DIM> Wall;
typedef std::array<TileLinkedListPtr, MOSAIC_DIM> PatternLines;
typedef TileLinkedListPtr FloorLinePtr;

class Mosaic {
 public:
  Mosaic();
  Mosaic(Wall&& wall, PatternLines&& pattern_lines, FloorLinePtr&& floor_line);
  Mosaic(Mosaic&& other);
  ~Mosaic();

  static Wall InitWall();
  static PatternLines InitPatternLines();

  // validate if a colour can go into a specific pattern line (or the floor
  // line), if valid, insert the tile_linked_list into the pattern_line
  // inserting overflowing tiles into the floor line in FIFO order
  // throws runtime_error if move is invalid
  void TryMove(Colour colour, unsigned int pattern_line,
               TileLinkedListPtr tile_linked_list);

  // return whether any row in the wall is full
  bool RowFull();

  // get score from pattern lines, move full pattern lines into wall, empty
  // remaining tiles from fill pattern lines into overflow
  int PatternScore();

  // calculate end game score from final wall tilings
  int EndGameWallScore();

  // calculate the floor penalty then empty the floor line into overflow
  // check whether first player tile is present
  int FloorPenalty();

  // return pointer to the floor line
  FloorLinePtr GetFloorLine();

  // return a pointe to the overflow TLL
  TileLinkedListPtr GetOverflow();

  // return whether the mosaic had the first player tile in the last round
  bool IsFirstPlayer();

  std::string ToString();
  std::string WallToString();
  std::string PatternLinesToString();
  std::string FloorLineToString();

 private:
  bool first_turn = false;
  Wall wall;
  PatternLines pattern_lines;
  FloorLinePtr floor_line;
  TileLinkedListPtr overflow;
  static const char* mos_wall[MOSAIC_DIM][MOSAIC_DIM];
};

#endif  // MOSAIC_H_
