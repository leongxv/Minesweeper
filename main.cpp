/*
Minesweeper Mini-game
 - 2D grid with bombs randomly placed
	- These locations are flagged as unsafe
 - Difference from regular minesweeper is:
 	- Spots where the bombs are not located have numbers that account for the distance from the closest bomb
*/

/*
Prompt:
1) g++ minesweeper.cpp minesweeper.h main.cpp
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
