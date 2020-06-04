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
    "\n\nMenu",
    "----",
    "1. New Game",
    "2. Load Game",
    "3. Credits (Show student information)",
    "4. Help",
    "5. Quit\n"};

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
        "=================================HELP===================================",
        "",
        "----Rules of the game:--------------------------------------------------",
        "Rules of the game are fairly simple, each users are to pick a color from",
        "the tile factories to be added to their mosiac. Once the left-hand side",
        "of the mosaic is fully filled with the same color, it will then be added",
        "to the RHS. The game ends after a player has completed a horizontal line",
        "of 5 consecutive tiles in their wall. Note: First player who picks from ",
        "the centre factory will acquire a -1 score penalty and each excess tile ",
        "picked that is unable to be added into the player's mosaic will be added",
        "to the broken tiles section where various penalties may apply. ",
        "PLAYER WITH THE HIGHEST SCORE WINS!!!!",
        "",
        "========================================================================",
        "",
        "----How to play Instructions:-------------------------------------------",
        "Each player starts by typing: turn <factory number> <tiles> <mosaic row>",
        "Where the first number inputted is the number of the factory chosen, ",
        "and the second value is the tile color that the player wishes to pick to",
        "be added to their own mosaic, and lastly the last number inputted is the",
        "number of row of the player's mosaic that the player wishes to add the",
        " tiles into.",
        "=============================ENJOY THE GAME!============================",
        "",
    };
    PrintList(help_ins, 25);
}

