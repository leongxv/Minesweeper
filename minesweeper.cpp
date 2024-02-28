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
#include <iomanip>
#include <vector>

using namespace std;

// Allocate the 2D array
void Sweepminer::allocateBoard()
{
	int maxDist = width + height + 1; // Maximum possible distance a space could be from bomb

	board = new int *[height];
	for (int i = 0; i < height; i++)
	{
		board[i] = new int[width];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			board[i][j] = maxDist;
		}
	}
}

// Deallocate the 2D array
void Sweepminer::deallocateBoard()
{
	for (int i = 0; i < height; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}

// Shows you the distance from the bomb going in various directions
void Sweepminer::generateDistances(Position pos, int distance)
{
	// Create bool so we can check in what direction we would like to go
	bool canGoLeft = true;
	bool canGoRight = true;
	bool canGoUp = true;
	bool canGoDown = true;

	// Call the set distance position function
	setDistanceAtPosition(pos, distance);

	// If statements to check if I can go in a certain direction

	// Check if the position of x is at 0, then set left boolean to false
	if (pos.x == 0)
	{
		canGoLeft = false;
	}

	/*
	Check if the position of x is equal to the width minus 1
	  - This means that the position hit out of the boundary of the box
	  - Therefore, you cannot move x position anymore
	  - Set right boolean to false
	*/
	if (pos.x == width - 1)
	{
		canGoRight = false;
	}

	// Check if the position of y is at 0, then set up boolean to false
	if (pos.y == 0)
	{
		canGoUp = false;
	}

	/*
	Check if the position of y is equal to height minus 1
	  - This means that the position hit out of the boundary of the box
	  - Therefore, you cannot move y position anymore
	  - Set down boolean to false
	*/
	if (pos.y == height - 1)
	{
		canGoDown = false;
	}

	// If statements for when the bool of the direction you want to go in is true

	// If right boolean is true
	if (canGoRight)
	{
		// Create an object of position that increases x by one and keeps y the same
		Position positiveX = Position(pos.x + 1, pos.y);

		/* Checks
			- if the object's x value is less than the width of the box
			- if it's greater than or equal to 0
			- if the distance at position of the object we created is greater than
				the position passed in
		*/
		if (positiveX.x < width && positiveX.x >= 0 && getDistanceAtPosition(positiveX) > distance + 1)
		{
			// Recursive function to keep increasing the distance depending on conditionals
			generateDistances(positiveX, distance + 1);
		}
	}

	// If down boolean is true
	if (canGoDown)
	{
		// Create an object of position that increases y by one and keeps x the same
		Position positiveY = Position(pos.x, pos.y + 1);

		if (positiveY.y < height && positiveY.y >= 0 && getDistanceAtPosition(positiveY) > distance + 1)
		{
			// Recursive function to keep increasing the distance depending on conditionals
			generateDistances(positiveY, distance + 1);
		}
	}

	// If left boolean is true
	if (canGoLeft)
	{
		// Create an object of position that decreases x by one and keeps y the same
		Position negativeX = Position(pos.x - 1, pos.y);

		if (negativeX.x < width && negativeX.x >= 0 && getDistanceAtPosition(negativeX) > distance + 1)
		{
			// Recursive function to keep increasing the distance depending on conditionals
			generateDistances(negativeX, distance + 1);
		}
	}

	// if up boolean is true
	if (canGoUp)
	{
		// Create an object of position that decreases y by one and keeps x the same
		Position negativeY = Position(pos.x, pos.y - 1);

		if (negativeY.y < height && negativeY.y >= 0 && getDistanceAtPosition(negativeY) > distance + 1)
		{
			// Recursive function to keep increasing the distance depending on conditionals
			generateDistances(negativeY, distance + 1);
		}
	}
}

// Popualte the board by randomly generating where the bombs go
void Sweepminer::populateBoard(const int &bomb_count)
{
	vector<Position> bombPositions;
	int i, j;
	Position *temp;
	bool duplicatePosition = false;

	for (i = 0; i < bomb_count; i++)
	{
		// Generate the next bomb position and make sure it's not a duplicate
		temp = new Position(rand() % width, rand() % height);
		while (duplicatePosition)
		{
			duplicatePosition = false;
			for (j = 0; j < (int)bombPositions.size(); j++)
			{
				if (bombPositions[j] == *temp)
				{
					duplicatePosition = true;
					break;
				}
			}
		}

		// Then, add the bomb and generate its distances
		generateDistances(*temp, 0); // Position is temp, distance to bomb is 0

		delete temp;
	}
}

// Prints all of the distances from the bomb
void Sweepminer::printBoard()
{
	int i, j;
	cout << setfill('-') << setw(3 * width + 3) << "" << setfill(' ') << endl; // Print top border
	for (i = 0; i < height; i++)
	{
		cout << "| "; // Print left border
		for (j = 0; j < width; j++)
		{
			if (board[i][j] == 0) // If this spot contains a bomb/flag, print its
				cout << " " << flag << " ";
			else // Else print the distance
				cout << setw(2) << right << board[i][j] << " ";
		}
		cout << "|" << endl; // Print right border
	}
	cout << setfill('-') << setw(3 * width + 3) << "" << setfill(' ') << endl; // Print bottom border
}