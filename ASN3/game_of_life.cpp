#include "game_of_life.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
//@author Jennifer Haselden
namespace GOL
{
    GameOfLife::GameOfLife(string filename) : GameOfLife(filename, '*', '-', 0) {}

    GameOfLife::GameOfLife(std::string filename, int generations) : GameOfLife(filename, '*', '-', generations) {}

    GameOfLife::GameOfLife(std::string filename, char live, char dead) : GameOfLife(filename, live, dead, 0) {}

    GameOfLife::GameOfLife(std::string filename, char live, char dead, int generations)
    {
        // Create a file input using the user's input
        fstream file_in(filename);
        if (!file_in)
        {
            throw(runtime_error("File not found as entered: please make sure file path is correct."));
        }
        if (!(file_in >> this->width_ >> this->height_))
        {
            throw(runtime_error("Invalid file format: first line must be width and height as an int, and the following lines must be the table."));
        }
        if (live == dead)
        {
            throw(runtime_error("Invalid arguments for live and dead cells; must be different characters."));
        }
        else
        {
            live_cell = live;
            dead_cell = dead;
        }
        // Pre Load "Current" with the "dead_cell" character as a rectangle table
        size_t size = width_ * height_;
        this->current_ = string(size, dead_cell);
        string line;

        // Skipping the end of the first line to get to the data
        // If you do not include this, then the first "getline" will get an empty string
        getline(file_in, line);

        // For all rows in the file
        for (int row = 0; row < this->height_; ++row)
        {
            getline(file_in, line);
            // For all Columns in the row
            for (int col = 0; col < this->width_; ++col)
            {
                // if the char is alive in the line, set it to be alive in current game
                if (line.at(col) == '*')
                {
                    living_cells++;
                    int replace_index = (row * width_) + col;
                    current_[replace_index] = live_cell;
                }
            }
        }
        NextNGen(generations);
    }

    void GameOfLife::NextGen()
    {
        std::string next_gen = current_; // initialize next gen string to current game
        // for all cells in the current_ game
        for (size_t i = 0; i < current_.length(); i++)
        {
            // check current cell's state
            bool alive = CheckCellState(i);

            // update live cell count
            if (alive)
            {
                living_cells++;
            }

            // check the current cell's neighbor's states
            int living_neighbors = CheckLivingNeighbors(i);

            // based on current cell state and neighbors of current cell, change cell state for next gen
            bool alive_in_next_gen = DetermineCellStateForNextGen(living_neighbors, alive);

            // track living cells of next gen
            if (alive_in_next_gen)
            {
                ++next_living_cells;
            }
            SetCellState(alive_in_next_gen, i, next_gen);
        }
        // when all cells have been accounted for - move on to next round
        CompleteNextGen(next_gen);
    }

    void GameOfLife::CompleteNextGen(string &next_gen_game)
    {
        SavePrevGen();
        current_ = next_gen_game;
        ++generations_;
        living_cells = next_living_cells;
    }

    void GameOfLife::SavePrevGen()
    {
        if (prev_game_count < 99)
        {
            // document game to save in prev_games array
            saved_game curr_game = {current_, live_cell, dead_cell};
            // cout << "current_ in SavePrevGen(): " << current_ << endl;
            prev_games[prev_game_count] = curr_game;
            ++prev_game_count;
            // for (int i = 0; i < prev_game_count; ++i){
            //     cout << prev_games[i].game_board << endl;
            // }
        } else {
            cout << "Max generations stored, cannot store more generations" << endl;
        }
    }

    void GameOfLife::NextNGen(int n)
    {
        for (int i = 0; i < n; i++)
        {
            NextGen();
        }
    }

    int GameOfLife::CheckLivingNeighbors(int cell_index)
    {
        int middle_row = Get2DRow(cell_index);
        int middle_col = Get2DCol(cell_index);
        int left_col = GetLeftCol(middle_col);
        int right_col = GetRightCol(middle_col);
        int upper_row = GetUpperRow(middle_row);
        int lower_row = GetLowerRow(middle_row);

        // array of cell neighbors
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
            if (current_.at(neighbor_index) == live_cell)
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

    bool GameOfLife::CheckCellState(size_t cell_index)
    {
        if (current_[cell_index] == live_cell)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void GameOfLife::SetCellState(bool alive, size_t cell_index, string &next_gen_game)
    {
        if (alive)
        {
            next_gen_game[cell_index] = live_cell;
        }
        else
        {
            next_gen_game[cell_index] = dead_cell;
        }
    }

    void GameOfLife::SetLiveCell(char new_char)
    {
        if (new_char == dead_cell)
        {
            throw(runtime_error("Error: New live cell cannot be same as current dead cell."));
        }
        else
        {
            // update current game with new char
            int len = current_.length();
            for (int i = 0; i < len; i++)
            {
                if (current_[i] == live_cell)
                {
                    current_[i] = new_char;
                }
            }
            live_cell = new_char;
        }
    }

    void GameOfLife::SetDeadCell(char new_char)
    {
        if (new_char == live_cell)
        {
            throw(runtime_error("Error: New dead cell cannot be same as current live cell."));
        }
        else
        {
            // update current game with new char
            int len = current_.length();
            for (int i = 0; i < len; i++)
            {
                if (current_[i] == dead_cell)
                {
                    current_[i] = new_char;
                }
            }
            dead_cell = new_char;
        }
    }

    int GameOfLife::Convert2DTo1D(int row, int col)
    {
        return (row * width_) + col;
    }

    int GameOfLife::Get2DCol(int index)
    {
        return index % width_;
    }

    int GameOfLife::GetLeftCol(int col)
    {
        return ((col - 1) + width_) % width_;
    }

    int GameOfLife::GetRightCol(int col)
    {
        return (col + 1) % width_;
    }

    int GameOfLife::Get2DRow(int index)
    {
        return index / width_;
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

    double GameOfLife::GetPercentLiving() const
    {
        double total_cells = width_ * height_;
        double percent_living = living_cells / total_cells;
        return percent_living * 100;
    }

    // TODO

    int GameOfLife::GetAvailableGens()
    {
        return prev_game_count;
    }

    // bool IsStillLife(){}

    void GameOfLife::ToggleCell(int index)
    {
        if (current_.at(index) == live_cell) // .at() throws range error
        {
            current_.at(index) = dead_cell;
            --living_cells;
        }
        else
        {
            current_.at(index) = live_cell;
            ++living_cells;
        }
    }

    void GameOfLife::ToggleCell(int row, int col)
    {
        ToggleCell(Convert2DTo1D(row, col));
    }

    // string GameOfLife::GenWindow(int row, int col, int height, int width)
    // {
    // }

    GameOfLife &GameOfLife::operator+=(int gens)
    {
        if (gens > 0)
        {
            this->NextNGen(gens);
            return *this;
        }
        else
        {
            return *this -= -gens;
        }
    }

    GameOfLife &GameOfLife::operator-=(int gens) {
        for (int i = 0; i < gens; ++i){
            --*this;
        }
        return *this;
    }

    GameOfLife GameOfLife::operator+(int gens) {
        if (gens > 0){
            GameOfLife copy = *this;
            copy.NextNGen(gens);
            return copy;
        }else {
            return *this - gens;
        }
    }

    GameOfLife GameOfLife::operator-(int gens) {
        for (int i = 0; i < gens; ++i){
            --*this;
        }
        return *this;
    }

    GameOfLife &GameOfLife::operator--() {
        if (prev_game_count == 0){
            throw std::domain_error("Cannot roll back generation, there are no previous generations.");
        }
        --prev_game_count;
        saved_game prev_saved_game = prev_games[prev_game_count];
        current_ = prev_saved_game.game_board;
        live_cell = prev_saved_game.live;
        dead_cell = prev_saved_game.dead;
        --generations_;
        return *this;
    }

    GameOfLife GameOfLife::operator--(int)
    {
        if (prev_game_count == 0){
            throw std::domain_error("Cannot roll back generation, there are no previous generations.");
        }
        GameOfLife prev_game = *this;
        --prev_game.prev_game_count;

        saved_game prev_saved_game = prev_games[prev_game_count];
        prev_game.current_ = prev_saved_game.game_board;
        prev_game.live_cell = prev_saved_game.live;
        prev_game.dead_cell = prev_saved_game.dead;
        --generations_;
        return prev_game;
    }

    GameOfLife GameOfLife::operator-()
    {
        GameOfLife neg_game = *this;
        for (size_t i = 0; i < neg_game.current_.length(); ++i)
        {
            neg_game.ToggleCell(static_cast<int>(i));
        }
        return neg_game;
    }

    GameOfLife &GameOfLife::operator++()
    {
        this->NextGen();
        return *this;
    }

    GameOfLife GameOfLife::operator++(int)
    {
        GameOfLife copy = *this;
        this->NextGen();
        return copy;
    }

    bool GameOfLife::operator<(const GameOfLife &other_game) const
    {
        double curr_percent_living = this->GetPercentLiving();
        double other_percent_living = other_game.GetPercentLiving();
        return curr_percent_living < other_percent_living;
    }

    bool GameOfLife::operator>(const GameOfLife &other_game) const
    {
        double curr_percent_living = this->GetPercentLiving();
        double other_percent_living = other_game.GetPercentLiving();
        return curr_percent_living > other_percent_living;
    }

    bool GameOfLife::operator==(const GameOfLife &other_game) const
    {
        bool compare = false;
        double curr_percent_living = this->GetPercentLiving();
        double other_percent_living = other_game.GetPercentLiving();
        if (curr_percent_living + .5 == other_percent_living || curr_percent_living - .5 == other_percent_living || curr_percent_living == other_percent_living)
        {
            compare = true;
        }
        return compare;
    }

    bool GameOfLife::operator<=(const GameOfLife &other_game) const
    {
        bool compare = false;
        double curr_percent_living = this->GetPercentLiving();
        double other_percent_living = other_game.GetPercentLiving();
        if (curr_percent_living + .5 <= other_percent_living || curr_percent_living - .5 <= other_percent_living || curr_percent_living <= other_percent_living)
        {
            compare = true;
        }
        return compare;
    }

    bool GameOfLife::operator>=(const GameOfLife &other_game) const
    {
        bool compare = false;
        double curr_percent_living = this->GetPercentLiving();
        double other_percent_living = other_game.GetPercentLiving();
        if (curr_percent_living + .5 >= other_percent_living || curr_percent_living - .5 >= other_percent_living || curr_percent_living >= other_percent_living)
        {
            compare = true;
        }
        return compare;
    }

    ostream &operator<<(ostream &os, const GameOfLife &game)
    {
        cout << "Generation: " << game.generations_ << endl;
        //os << game.current_ << endl;

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
