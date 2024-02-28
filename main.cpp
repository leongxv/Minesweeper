/*
main.cpp
 - Calls the functions in minesweeper.cpp to implement the minesweeper board
*/

#include "minesweeper.h"
#include <cstdlib>
#include <iostream>

using namespace std;

const int BOMB_COUNT = 5;
const int MINESWEEPER_WIDTH = 16;
const int MINESWEEPER_HEIGHT = 8;

int main()
{
	Sweepminer sweepminer =  //Make the board
	Sweepminer(MINESWEEPER_WIDTH, MINESWEEPER_HEIGHT, BOMB_COUNT); 
	sweepminer.printBoard(); //Print the result for testing

	return 0;
}
