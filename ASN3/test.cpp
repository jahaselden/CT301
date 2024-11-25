#include "game_of_life.h"
#include <iostream>

using namespace std;
using namespace GOL;

int main(int argc, char const *argv[])
{
    GameOfLife game("starter.txt");
    cout << game;
    game.NextGen();
    cout << game;
    cout << ++game;
	// cout << (game + 10);
	// cout << game; 
    cout << endl << "Negation operator: " << endl;
    cout << -game;
    cout << game; 

    cout << endl << "Copy Assignment: " << endl;
    GameOfLife game_copy(game);
    cout << game_copy;

    // cout << endl << "Decrement Game: " << endl;
    // cout << game_copy--;

    cout << endl << "Pre-decriment operator: " << endl;
    cout << --game;
    cout << --game;

    ++game;
    ++game;

    cout << endl << "Pre-decriment operator with -2: " << endl;
    cout << game - 2;

    cout << endl << "Decriment equals operator +2: " << endl;
    game += 2;
    cout << game;

    cout << endl << "Decriment equals operator -2: " << endl;
    game += -2;
    cout << game;


    //cout << "Previous gens should be 0: " << game_copy.GetAvailableGens() << endl;

    // GameOfLife game("starter_2.txt", 'l', '-');
    // cout << game;
    // game.NextGen();
    // cout << ++game;
	// cout << (game + 10);
	// cout << game;

    return 0;
}