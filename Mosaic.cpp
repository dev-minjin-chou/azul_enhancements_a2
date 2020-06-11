// Copyright 2020 Chou, Dechathaweewat, Hollis-London

#include "Mosaic.h"

#include <sstream>
#include <iostream>

Mosaic::Mosaic()
{
  this->wall = Mosaic::InitWall();
  this->pattern_lines = Mosaic::InitPatternLines();
  this->floor_line = std::make_shared<TileLinkedList>();
  this->overflow = std::make_shared<TileLinkedList>();
};

Mosaic::~Mosaic() {}

Mosaic::Mosaic(Wall &&wall, PatternLines &&pattern_lines,
               FloorLinePtr &&floor_line)
    : wall(std::move(wall)),
      pattern_lines(std::move(pattern_lines)),
      floor_line(std::move(floor_line))
{
  this->overflow = std::make_shared<TileLinkedList>();
};

Mosaic::Mosaic(Mosaic &&other)
    : wall(std::move(other.wall)),
      pattern_lines(std::move(other.pattern_lines)),
      floor_line(std::move(other.floor_line)),
      overflow(std::move(other.overflow)){};

Wall Mosaic::InitWall()
{
  Wall wall = Wall();
  for (size_t i = 0; i < MOSAIC_DIM; i++)
  {
    wall.at(i) = std::array<TilePtr, MOSAIC_DIM>();
    for (size_t j = 0; j < MOSAIC_DIM; j++)
    {
      wall.at(i).at(j) = nullptr;
    }
  }
  return wall;
}

PatternLines Mosaic::InitPatternLines()
{
  PatternLines pattern_lines = PatternLines();
  for (size_t i = 0; i < MOSAIC_DIM; i++)
  {
    pattern_lines.at(i) = std::make_shared<TileLinkedList>();
  }
  return pattern_lines;
}

bool Mosaic::RowFull()
{
  bool any_row_full = false;
  for (size_t i = 0; i < MOSAIC_DIM && !any_row_full; i++)
  {
    bool row_full = true;
    for (size_t j = 0; j < MOSAIC_DIM; j++)
    {
      if (this->wall.at(i).at(j) == nullptr)
        row_full = false;
    }
    if (row_full)
      any_row_full = true;
  }
  return any_row_full;
}

int colour_index(Colour colour, int i)
{
  // get index of tile colour on wall row using python style modulo
  int n = (int)Colour::B + i - colour;
  int M = TILE_SZ - 1;
  // python style modulo
  return ((n % M) + M) % M;
}

int Mosaic::PatternScore()
{
  int score = 0;
  for (int i = 0; i < MOSAIC_DIM; i++)
  {
    TileLinkedListPtr pattern_line = this->pattern_lines.at(i);
    if ((int)pattern_line->Size() == i + 1)
    {
      // pattern line is full
      // plus 1 to score
      score += 1;
      Colour colour = pattern_line->GetColour();
      int index = colour_index(colour, i);
      // find horizontally linked adjacent tiles
      std::array<TilePtr, MOSAIC_DIM> &wall_row = this->wall.at(i);
      // forward
      int a = 0;
      for (a = index + 1; a < MOSAIC_DIM && wall_row.at(a) != nullptr; a++)
      {
        score += 1;
      }
      // backward
      for (a = index - 1; a >= 0 && wall_row.at(a) != nullptr; a--)
      {
        score += 1;
      }
      // find vertically linked adjacent tiles
      // upwards
      for (a = i - 1; a >= 0 && this->wall.at(a).at(index) != nullptr; a--)
      {
        score += 1;
      }
      // downwards
      for (a = i + 1; a < MOSAIC_DIM && this->wall.at(a).at(index) != nullptr;
           a++)
      {
        score += 1;
      }
      // move tile to wall
      TilePtr tile = pattern_line->RemoveBack();
      wall_row.at(index) = std::move(tile);
      // empty pattern_line into overflow
      while (pattern_line->Size() > 0)
        this->overflow->AddTile(pattern_line->RemoveFront());
    }
  }
  return score;
}

int Mosaic::EndGameWallScore()
{
  int score = 0;
  // full rows
  // full columns
  // completed colours
  std::array<int, MOSAIC_DIM> colour_tally = std::array<int, MOSAIC_DIM>();
  for (size_t i = 0; i < MOSAIC_DIM; i++)
  {
    bool row_full = true;
    bool col_full = true;
    for (size_t j = 0; j < MOSAIC_DIM; j++)
    {
      if (this->wall.at(i).at(j) == nullptr)
        row_full = false;
      if (this->wall.at(j).at(i) == nullptr)
        col_full = false;
      int colour = (int)this->wall.at(i).at(j)->GetColour();
      colour_tally.at(colour)++;
      if (colour_tally.at(colour) == MOSAIC_DIM)
        score += 10;
    }
    if (row_full)
      score += ROW_FULL_BONUS;
    if (col_full)
      score += COL_FULL_BONUS;
  }
  return score;
}

void Mosaic::TryMove(Colour colour, unsigned int pattern_line,
                     TileLinkedListPtr tile_linked_list)
{
  unsigned int line_size_limit = 0;

  if (pattern_line != FLOOR_INDEX)
  {
    // f tile must go in floor line
    if (colour == Colour::F)
      throw std::runtime_error("F tile must go in floor line");
    // pattern line must not be full
    TileLinkedListPtr pattern_line_ptr = this->pattern_lines.at(pattern_line);
    if (pattern_line_ptr->Size() >= pattern_line + 1)
      throw std::runtime_error("pattern line is full");
    //  must be empty or the colour of the colour
    // parameter
    if (pattern_line_ptr->Size() > 0 && pattern_line_ptr->GetColour() != colour)
      throw std::runtime_error("pattern line is different colour");
    // colour must not be present in adjacent wall row
    for (size_t i = 0; i < MOSAIC_DIM; i++)
    {
      TilePtr &cell = this->wall.at(pattern_line).at(i);
      if (cell != nullptr && cell->GetColour() == colour)
        throw std::runtime_error("wall already contains colour");
    }
    // set amount of tiles that can go into the pattern line
    line_size_limit = pattern_line + 1 - pattern_line_ptr->Size();
  }
  //  move is valid

  // add tiles to selected pattern line until pattern line size limit is
  // reached (will skip if line_size_limit is 0)
  while (tile_linked_list->Size() > 0 && line_size_limit > 0)
  {
    this->pattern_lines.at(pattern_line)
        ->AddTile(tile_linked_list->RemoveFront());
    line_size_limit--;
  }
  // add remaining tiles to floor line (will add all tiles to floor line if
  // line size limit is 0) until floor line is full
  while (tile_linked_list->Size() > 0 && this->floor_line->Size() < FLOOR_SZ)
  {
    this->floor_line->AddTile(tile_linked_list->RemoveFront());
  }
  // add remaining remaining to hidden TLL overflow to be emptied by Game
  while (tile_linked_list->Size() > 0)
  {
    this->overflow->AddTile(tile_linked_list->RemoveFront());
  }
}

int Mosaic::FloorPenalty()
{
  this->first_turn = false;
  int count = 0;
  if (floor_line->Size() != 0)
  {
    for (unsigned int i = 0; i < floor_line->Size(); i++)
    {
      count += 1;
      if (i > 1)
      {
        count += 1;
      }
      if (i > 4)
      {
        count += 1;
      }
    }
    while (floor_line->Size() > 0)
    {
      TilePtr tile = floor_line->RemoveFront();
      if (tile->GetColour() == Colour::F)
      {
        this->first_turn = true;
      }
      else
      {
        this->overflow->AddTile(std::move(tile));
      }
      // first player tile is dropped here
    }
  }
  return count;
}

bool Mosaic::IsFirstPlayer() { return this->first_turn; }

FloorLinePtr Mosaic::GetFloorLine() { return this->floor_line; }

TileLinkedListPtr Mosaic::GetOverflow() { return this->overflow; }

string Mosaic::PatternLinesToString()
{
  std::stringstream ss;
  for (size_t i = 0; i < MOSAIC_DIM; i++)
  {
    std::string pl = this->pattern_lines.at(i)->ToSaveString();
    while (pl.size() < i + 1)
      pl = "." + pl;
    ss << pl << std::endl;
  }
  return ss.str();
}

std::string Mosaic::WallToString()
{
  std::stringstream ss;
  // wall
  for (size_t i = 0; i < MOSAIC_DIM; i++)
  {
    for (size_t j = 0; j < MOSAIC_DIM; j++)
    {
      if (this->wall.at(i).at(j) == nullptr)
      {
        ss << ".";
      }
      else
      {
        ss << this->wall.at(i).at(j)->ToString();
      }
    }
    ss << std::endl;
  }
  return ss.str();
}

std::string Mosaic::FloorLineToString()
{
  std::string fl = this->floor_line->ToSaveString();
  while (fl.size() < FLOOR_SZ)
    fl.append(".");
  return fl + "\n";
}

const char *Mosaic::mos_wall[MOSAIC_DIM][MOSAIC_DIM] = {
    {" B", " Y", " R", " U", " L"},
    {" L", " B", " Y", " R", " U"},
    {" U", " L", " B", " Y", " R"},
    {" R", " U", " L", " B", " Y"},
    {" Y", " R", " U", " L", " B"},
};

std::string Mosaic::ToString()
{
  std::stringstream ss;
  for (size_t i = 0; i < MOSAIC_DIM; i++)
  {
    ss << i + 1 << ": ";
    // # Pattern Line #
    // spacing offset
    unsigned int offset = MOSAIC_DIM - (i + 1);
    for (size_t j = 0; j < offset; j++)
      ss << "  ";
    // empty tiles
    unsigned int empty_count = (i + 1) - this->pattern_lines.at(i)->Size();
    for (size_t j = 0; j < empty_count; j++)
      ss << ". ";
    ss << this->pattern_lines.at(i)->backgroundToString();
    ss << "||";
    // wall
    for (size_t j = 0; j < MOSAIC_DIM; j++)
    {
      if (this->wall.at(i).at(j) == nullptr)
      {
        ss << mos_wall[i][j];
      }
      else
      {
        ss << " " << this->wall.at(i).at(j)->colouredBGToString();
      }
    }
    ss << std::endl;
  }
  // floor line (broken)
  ss <<"\u001b[31mbroken: \u001b[0m" << this->floor_line->ToString();
  return ss.str();
}