#include "Menu.h"

#include <stdlib.h>

#include <iostream>

void Menu::PrintList(const char* list[], unsigned int len) {
  for (size_t i = 0; i < len; i++) {
    std::cout << list[i] << std::endl;
  }
};
const int Menu::main_len = 7;
const char* Menu::main_menu[Menu::main_len] = {
    "\n\n\u001b[34;1mMenu\u001b[0m",
    "\u001b[37m----\u001b[0m",
    "1. \u001b[35;1m\u0145ew Game \u001b[0m ",
    "2. \u001b[32m\u013Foad Game \u001b[0m",
    "3. \u001b[36m\u0187redits \u001b[0m",
    "4. \u001b[33mHelp (\u00BF) \u001b[0m",
    "5. \u001b[31mQuit (\u00D7) \u001b[0m\n"};

void Menu::Main() { PrintList(main_menu, main_len); }

// TODO fix segmentation fault
void Menu::Credits() {
  const char* credits_list[] = {
      "",
      "----------------------------------",
      "Name: Minjin Chou",
      "Student ID: s3641315",
      "Email: s3641315@student.rmit.edu.au",
      "",
      "Name: Chatchapat Dechathaweewat",
      "Student ID: s3679216",
      "Email: s3679216@student.rmit.edu.au"
      "",
      "Name: Jack Hollis-London",
      "Student ID: s3585034",
      "Email: s3585034@student.rmit.edu.au",
      "----------------------------------",
      "",
  };
  PrintList(credits_list, 14);
}

void Menu::Instructions() {
    
    const char* help_ins[] = {
        "",
        "==================HELP==================",
        "",
        "---Rules of the game:-------------------",
        "Rules of the game are fairly simple.    ",
        "1. Pick a tile color from the factory.  ",
        "2. Place the tile in your mosaic.       ",
        "3. If LHS is fully filled with same tile",
        "4. Completed row tile is added to RHS   ",
        "5. Game ends if a col is filled on RHS  ",
        "Note: Penalty applies to broken tiles.  ",
        "",
        "========================================",
        "",
        "---How to play Instructions:------------",
        "1. Play by typing: turn '2''R''3'     ",
        "turn <factory number><tiles><mosaic row>",
        "2.Save the game by typing:save/save name",
        "save <FileName>                         ",
        "=============ENJOY THE GAME!============",
        "",
    };
    PrintList(help_ins, 21);
}

