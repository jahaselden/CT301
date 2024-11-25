#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED
#include <iostream>
#include <string>
//@author Jennifer Haselden
namespace GOL
{
  class GameOfLife
  {
    /***
     * @brief int width_, this integer stores the value for the width of the game table
     */
    int width_;

    /**
     * @brief int height_, this integer stores the value for the height of the game table
     */
    int height_;

    /**
     * @brief generations_, the counter of generations of the game
     */
    int generations_ = 0;

    /**
     * @brief dead_cell, the char representing dead cells in the game table
     */
    char dead_cell = '-';

    /**
     * @brief live_cell, the char representing the live cells in the game table
     */
    char live_cell = '*';

    /**
     * @brief current_, the current game of life as a string
     */
    std::string current_;

    /**
     * @brief living_cells, the running total of living_cells in current game
     */
    int living_cells = 0;

    /**
     * @brief next_living_cells, the running total of living cells in next gen of game
     */
    int next_living_cells = 0;

    /**
     * @brief saved_game, the state of data relating to previous generations
     */
    struct saved_game
    {
      /**
       * game_board represents the string of a game
       */
      std::string game_board;

      /**
       * live is the character representing live cells
       */
      char live;

      /**
       * dead is the character representing dead cells 
       */
      char dead;
    };

    /**
     * @brief prev_games, stores previous generations
     */
    saved_game prev_games[100];

    /**
     * @brief prev_game_count, stores number of gens in array
     */
    int prev_game_count = 0;

  public:
    /**
     * Destructor
     * @brief Cleans up all memory allocations.;
     */
    ~GameOfLife() = default;

    /**
     * Assignment Operator
     * @param game reference to a game of life object
     */
    GameOfLife &operator=(const GameOfLife &game) = default;

    /**
     * Copy Constructor
     * @param old_game reference to a game to copy
     */
    GameOfLife(const GameOfLife &old_game) = default;

    /**
     * GameOfLife
     * this constructor loads a game of life with the user's input file
     * @param filename is a file that represents the "current" game of life
     */
    GameOfLife(std::string filename);

    /**
     * GameOfLife
     * contructor loads a game of life with the user's input file
     * @param filename is a file that represents the "current" game of life
     * @param generations is an int representing the number of generations
     */
    GameOfLife(std::string filename, int generations);

    /**
     * GameOfLife
     * contructor loads a game of life with the user's input file
     * @param filename is a file that represents the "current" game of life
     * @param live is a char representing a live cell
     * @param dead is a char representing a dead cell
     */
    GameOfLife(std::string filename, char live, char dead);

    /**
     * GameOfLife
     * contructor loads a game of life with the user's input file
     * @param filename is a file that represents the "current" game of life
     * @param live is a char representing a live cell
     * @param dead is a char representing a dead cell
     * @param generations is an int representing the number of generations
     */
    GameOfLife(std::string filename, char live, char dead, int generations);

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

    /**
     * SetLiveCell
     * changes current live cell to a different character, cannot be set to same as dead cell
     * @param new_char the character to change live cell to
     * @throws a runtime error if live cell is same as dead
     */
    void SetLiveCell(char new_char);

    /**
     * SetDeadCell
     * changes current dead cell to a different character, cannot be set to same as live cell
     * @param new_char the character to change dead cell to
     * @throws a runtime error if dead cell is same as live
     */
    void SetDeadCell(char new_char);

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
     * GetPercentLiving
     * @returns the value of living cells as a percent of all cells
     */
    double GetPercentLiving() const;

    /**
     * @returns the count of the available gens for rollback for the '-' operators
     */
    int GetAvailableGens();

    /**
     * 
     */
    bool IsStillLife();

    /**
     * @brief sets a live_cell at the index to a dead_cell and vice versa
     * @param index to toggle in current game
     */
    void ToggleCell(int index);

    /**
     * @brief sets a live_cell at the index to a dead_cell and vice versa
     * @param row of index to toggle
     * @param col of index to toggle
     */
    void ToggleCell(int row, int col);

    /**
     * 
     */
    std::string GenWindow(int row, int col, int height, int width);

    /**
     * @brief calculates the next generation and then returns itself
     */
    GameOfLife &operator++();

    /**
     * @brief calculates the next generation but returns an instance of the game before incrementing
     */
    GameOfLife operator++(int);

    /**
     * @brief calculates the Next int N generations for the current game of life and returns itself
     * @param int to determine number of generations, accomodates negatives
     */
    GameOfLife &operator+=(int gens);

    /**
     * @brief
     */
    GameOfLife &operator-=(int gens);

    /**
     * @brief creates a copy of the game and calculates what the game would look like in int N generations and returns that copy
     * @param int to determine number of generations, accomodates negatives
     */
    GameOfLife operator+(int gens);

    /**
     * @brief
     */
    GameOfLife operator-(int gens);

    /**
     * @brief
     */
    GameOfLife &operator--();

    /**
     * @brief
     */
    GameOfLife operator--(int);

    /**
     * @brief
     */
    GameOfLife operator-();

    /**
     * == operator overload function
     * @returns true if two games are Equal to one another, aka within 0.5% living of one another
     */
    bool operator==(const GameOfLife &) const;

    /**
     * < operator overload function
     * @returns true if this game is STRICTLY Less than another game
     */
    bool operator<(const GameOfLife &) const;

    /**
     * > operator overload function
     * @returns true if this game is STRICTLY Greater than another game
     */
    bool operator>(const GameOfLife &) const;

    /**
     * <= operator overload function
     * @returns true if this game is Less Than OR Within 0.5% living of another game
     */
    bool operator<=(const GameOfLife &) const;

    /**
     * >= operator overload function
     * @returns true if this game is Greater Than OR Within 0.5% living of another game
     */
    bool operator>=(const GameOfLife &) const;

    // NOTE: Nothing needed for a friend statement
    friend std::ostream &operator<<(std::ostream &os, const GameOfLife &game);
  };

  /**
   * << operator overload function
   * @param os the ostream object to print to console
   * @param game the game to print
   */
  std::ostream &operator<<(std::ostream &os, const GameOfLife &game);

}

#endif