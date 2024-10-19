#include "game_of_life.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
//@author Jennifer Haselden
// Include the Namespace for Game of Life
namespace GOL
{
    GameOfLife::GameOfLife(string filename)
    {
        // Create a file input using the user's input
        fstream file_in(filename);
        if (!file_in)
        {
            // File not found
            throw(runtime_error("File not found as entered: please make sure file path is correct"));
        }
        if (!(file_in >> this->width_))
        {
            // Invalid file format
            throw(runtime_error("Invalid file format: first line must be width as an int, and the following lines must be the table"));
        }
        // Pre Load "Current" with the "dead_cell" character as a square table
        // Remember that the default dead character is '-'
        this->height_ = width_;
        size_t size = width_ * height_;
        this->current_ = string(size, '-'); /*look up string fill ctor*/

        string line;
        getline(file_in, line);
        // Skipping the end of the first line to get to the data
        // If you do not include this, then the first "getline"
        // will get an empty string
        // For all rows in the file
        for (int row = 0; row < this->width_; ++row)
        {
            getline(file_in, line);
            // For all Columns in the row
            for (int col = 0; col < this->height_; ++col)
            {
                // TODO: When you find a "living" character inside of "line"
                // Set the character at the same index inside of current to be "live"
                // Remember that the default live character is '*'
                // Check the assignment page for the math logic for 2d to 1d conversion

                // if the char is alive in the line, set it to be alive in current game
                if (line.at(col) == '*')
                {
                    int replace_index = (row * width_) + col;
                    current_[replace_index] = '*';
                }
            }
        }
    }

    int GameOfLife::Convert2DTo1D(int row, int col)
    {
        return (row * width_) + col;
    }

    int GameOfLife::Get2DRow(int index)
    {
        return index / width_;
    }

    int GameOfLife::Get2DCol(int index)
    {
        return index % height_;
    }

    void GameOfLife::NextGen()
    {
        std::string next_gen = current_; // initialize next gen string to current game

        // for all cells in the current_ game
        for (size_t i = 0; i < current_.length(); i++)
        {
            // check current cell's state
            bool alive = CheckCellState(i);

            // check the current cell's neighbor's states
            int living_neighbors = CheckLivingNeighbors(i);

            // based on current cell state and neighbors of current cell, change
            // cell state for next gen
            bool alive_in_next_gen = DetermineCellStateForNextGen(living_neighbors, alive);
            SetCellState(alive_in_next_gen, i, next_gen);
        }
        // when all cells have been accounted for - move on to next round
        CompleteNextGen(next_gen);
    }

    int GameOfLife::CheckLivingNeighbors(int cell_index) // might need to be size_t
    {
        int middle_row = Get2DRow(cell_index);
        int middle_col = Get2DCol(cell_index);
        int left_col = GetLeftCol(middle_col);
        int right_col = GetRightCol(middle_col);
        int upper_row = GetUpperRow(middle_row);
        int lower_row = GetLowerRow(middle_row);

        // int up_left = Convert2DTo1D(upper_row, left_col);
        // int middle_left = Convert2DTo1D(middle_row, left_col);
        // int lower_left = Convert2DTo1D(lower_row, left_col);
        // int up_middle = Convert2DTo1D(upper_row, middle_col);
        // int down_middle = Convert2DTo1D(lower_row, middle_col);
        // int up_right = Convert2DTo1D(upper_row, right_col);
        // int middle_right = Convert2DTo1D(middle_row, right_col);
        // int lower_right = Convert2DTo1D(lower_row, right_col);

        // try array loop instead of a bunch of if else statements for comparison
        int neighbors[8] = {Convert2DTo1D(upper_row, left_col),
                            Convert2DTo1D(middle_row, left_col),
                            Convert2DTo1D(lower_row, left_col),
                            Convert2DTo1D(upper_row, middle_col),
                            Convert2DTo1D(lower_row, middle_col),
                            Convert2DTo1D(upper_row, right_col),
                            Convert2DTo1D(middle_row, right_col),
                            Convert2DTo1D(lower_row, right_col)};

        int living_neighbors = 0;

        // increment living_neighbors if char is * of cell
        for (int neighbor_index : neighbors)
        {
            if (current_.at(neighbor_index) == '*')
            {
                living_neighbors++;
            }
        }

        return living_neighbors;
    }

    bool GameOfLife::DetermineCellStateForNextGen(int living_neighbors, bool alive)
    {
        bool alive_in_next_gen = false;
        if (alive == true)
        {
            // A live cell with two or three live neighbors lives on to the next generation
            if (living_neighbors == 2 || living_neighbors == 3)
            {
                alive_in_next_gen = true;
            }
            // A live cell with fewer than two live neighbors dies (underpopulation)
            // A live cell with more than three live neighbors dies (overpopulation)
            else
            {
                alive_in_next_gen = false;
            }
        }
        // A dead cell with exactly three live neighbors comes to life (rebirth)
        else if (alive == false && living_neighbors == 3)
        {
            alive_in_next_gen = true;
        }
        return alive_in_next_gen;
    }

    void GameOfLife::SetCellState(bool alive, size_t cell_index, string &next_gen_game)
    {
        if (alive)
        {
            next_gen_game[cell_index] = '*';
        }
        else
        {
            next_gen_game[cell_index] = '-';
        }
    }

    void GameOfLife::CompleteNextGen(string &next_gen_game)
    {
        current_ = next_gen_game;
        generations_++;
    }

    bool GameOfLife::CheckCellState(size_t cell_index)
    {
        if (current_[cell_index] == '*')
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void GameOfLife::NextNGen(int n)
    {
        if (n > 0)
        {
            for (int i = 0; i < n; i++)
            {
                NextGen();
            }
        }
    }

    int GameOfLife::GetLeftCol(int col)
    {
        return ((col - 1) + width_) % width_;
    }

    int GameOfLife::GetRightCol(int col)
    {
        return (col + 1) % width_;
    }

    int GameOfLife::GetUpperRow(int row)
    {
        return ((row - 1) + height_) % height_;
    }

    int GameOfLife::GetLowerRow(int row)
    {
        return (row + 1) % height_;
    }

    int GameOfLife::GetGenerations()
    {
        return generations_;
    }

    // TODO Finish the Operator<< method for outputting your game of life
    ostream &operator<<(ostream &os, const GameOfLife &game)
    {
        cout << "Generation: " << game.generations_ << endl;

        for (size_t i = 0; i < game.current_.length() + 1; i++)
        {
            os << game.current_[i];
            if ((i + 1) % game.width_ == 0)
            {
                os << endl;
            }
        }

        return os;
    }
}
