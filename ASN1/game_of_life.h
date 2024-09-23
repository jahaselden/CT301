#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED
#include <iostream>
#include <string>
//@author Your name goes here
namespace /*insert correct namespace name*/ {
class game_of_life {
  // Insert Data Member Variables here
  /***
   * int width_, this integer stores the value for the width and height
   * of the game table
   * TODO: INCLUDE THE OTHER 2 CLASS MEMBER VARIABLES
   */
  int width_;
  int generations_ = 0;
  std::string current_;

 public:
  // No need to include a doxygen comment for a deleted ctor
  game_of_life() = delete;
  // TODO Write Doxygen comment for this constructor,
  // Look at the implementation in game_of_life.cpp for reference
  game_of_life(std::string filename);
  //TODO Define the Remaining Methods of Game of Life here
  //NOTE: Nothing needed for a friend statement
  friend std::ostream &operator<<(std::ostream &os, const game_of_life &game);
};
//TODO Write a Doxygen comment for your output operator function
std::ostream &operator<<(std::ostream &os, const game_of_life &game);
}

#endif