#include "game_of_life.h"
#include <iostream>

using namespace std;
using namespace GOL;

int main(int argc, char const *argv[])
{
    GameOfLife game("starter.txt");
    cout << game;
    game.NextGen();
    cout << ++game;
	cout << (game + 10);
	cout << game;
    return 0;
}