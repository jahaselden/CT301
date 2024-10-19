#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED
#include <iostream>
#include <string>
//@author Jennifer Haselden
namespace GOL
{
  class GameOfLife
  {
    // Insert Data Member Variables here
    /***
     * int width_, this integer stores the value for the width and height
     * of the game table
     * TODO: INCLUDE THE OTHER 2 CLASS MEMBER VARIABLES
     */
    int width_;
    int height_; // use to make asgn2 easier?
    int generations_ = 0;
    std::string current_;

  public:
    GameOfLife() = delete;

    /**
     * game_of_life
     * this constructor loads a game of life with the user's input file
     * @param filename is a file that represents the "current" game of life
     */
    GameOfLife(std::string filename);
    // TODO Define the Remaining Methods of Game of Life here
    // and their doxygen

    /**
     * Convert2DTo1D
     * @param row is the row number of 2D structure
     * @param col is the col number of 2D structure
     * @returns an int to index into 1D format string
     */
    int Convert2DTo1D(int row, int col);

    /**
     * Get2DRow
     * @param index is an index in 1D format to be converted to row
     * @returns an int that represents the row of passed index
     */
    int Get2DRow(int index);

    /**
     * Get2DCol
     * @param index is an index in 1D format to be converted to col
     * @returns an int that represents the col of passed index
     */
    int Get2DCol(int index);

    /**
     * NextGen
     * Calculates the next generation of the game and increments generation count
     */
    void NextGen();

    /**
     * CheckLivingNeighbors
     * @param cell_index is the cell to check surrounding neighbors in current_ game
     * @returns an int with number of living neighbors of passed cell
     */
    int CheckLivingNeighbors(int cell_index);

    /**
     * GetLeftCol
     * @param col the current column of the cell
     * @returns the col to the left of the cell
     */
    int GetLeftCol(int col);

    /**
     * GetRightCol
     * @param col the current column of the cell
     * @returns the col to the right of the cell
     */
    int GetRightCol(int col);

    /**
     * GetUpperRow
     * @param row the current row of the cell
     * @returns the row above the current cell
     */
    int GetUpperRow(int row);

    /**
     * GetLowerRow
     * @param row the current row of the cell
     * @returns the row below the current cell
     */
    int GetLowerRow(int row);

    /**
     * DetermineCellStateForNextGen
     * @param living_neighbors an int representing number of live neighbors
     * @returns a boolean that represents if a cell will be alive (true), or dead (false)
     * in the next gen based on the rules of Game of Life & number of alive neighbors
     */
    bool DetermineCellStateForNextGen(int living_neighbors, bool alive);

    /**
     * CheckCellState
     * @param cell_index to check state
     * @returns boolean representing current state of alive or dead (true or false)
     */
    bool CheckCellState(size_t cell_index);

    /**
     * SetCellState
     * @param alive_in_next_gen is the bool representing if a cell will be alive (true), or dead
     * (false) in next round
     * @param cell_index the cell that needs dead or alive state to be set
     * @param next_gen_game a string that represents what will be set to the next gen
     * after round completes
     */
    void SetCellState(bool alive, size_t cell_index, std::string &next_gen_game);

    /**
     * CompleteNextGen
     * @param next_gen_game is set as the current_ game once all cells have been updated
     */
    void CompleteNextGen(std::string &next_gen_game);

    /**
     * NextNGen
     * @param n the number of times to run the NextGen() method, ignores n < 1
     */
    void NextNGen(int n);

    /**
     * GetGenerations
     * @returns the number of generations
     */
    int GetGenerations();

    // NOTE: Nothing needed for a friend statement
    friend std::ostream &operator<<(std::ostream &os, const GameOfLife &game);
  };
  // TODO Write a Doxygen comment for your output operator function
  std::ostream &operator<<(std::ostream &os, const GameOfLife &game);
}

#endif