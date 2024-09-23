#include "game_of_life.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
//@author Your name goes here
//TODO: Include the Namespace for Game of Life

game_of_life::game_of_life(string filename) {
  // Create a file input using the user's input
  fstream file_in(filename);
  if (!file_in) {
    // File not found
    throw(runtime_error(/*FINISH THIS ERROR MESSAGE*/));
  }
  if (!(file_in >> this->width_)) {
    // Invalid file format
    throw(runtime_error(/*FINISH THIS ERROR MESSAGE*/))
  }
  // Pre Load "Current" with the "dead_cell" character as a square table
  this->current_ = "";/*look up string fill ctor*/
  // Remember that the default dead character is '-'
  string line;
  getline(file_in, line);
  // Skipping the end of the first line to get to the data
  // If you do not include this, then the first "getline"
  // will get an empty string
  // For all rows in the file
  for (int row = 0; row < this->width_; ++row) {
    getline(file_in, line);
    // For all Columns in the row
    for (int col = 0; col < this->width_; ++col) {
      // TODO: When you find a "living" character inside of "line"
      // Set the character at the same index inside of current to be "live"
      // Remember that the default live character is '*'
      // Check the assignment page for the math logic for 2d to 1d conversion
    }
  }
}
//TODO Implement the Game of Life Functions

//TODO Finish the Operator<< method for outputting your game of life
ostream &operator<<(ostream &os, const game_of_life &game) {
  return os;
}