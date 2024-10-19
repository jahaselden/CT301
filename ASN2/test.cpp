#include <iostream>
#include "game_of_life.h"
using namespace std;
int main(int argc, char const *argv[])
{
	GOL::GameOfLife game("gamestarter.txt");
	cout << game;
	game.NextGen();
	cout << game;
	for (size_t i = 0; i < 5; i++)
	{
		game.NextGen();
	}
	cout << game;
	return 0;
}