/* Character and Room header, holds struct of character and room
 * By: Berkeley Savage/Anthony Nguyen
 * 10/20/2020
*/

#include <string>
#include <iostream>

using namespace std;

// Start of important header guard.
#ifndef CHARANDROOM_H
#define CHARANDROOM_H

// Character Struct!
// Technically, our Player uses -> name, status, str, dex, intl, hitPoints, gold, and key.
// And enemies use -> name, status, str, hitPoints, gold, and art[] (along with printArt()).
// But because we never call something the Character doesn't use, it works out really nicely.
struct Character
{
	std::string name;
	bool status; // False/0: Dead True/1: Alive
	int str;
	int dex;
	int intl;	
	int hitPoints;
	int gold;
	bool key; // False/0: No key True/1: Key -> MUST HAVE A KEY TO EXIT
	
	string art[6];  // [0] -> Line 1 [1] -> Line 2...
	
	void printArt()
	{
		// Used for printing Enemy art in fights. See more in Encounter.cpp
		cout << "- - - - - - -" << endl;
		for(int i = 0; i < 6; i++)
		{
			cout << art[i] << endl;
		}
		cout << "- - - - - - -" << endl;
		cout << "Enemy Name: " << name << endl;
		cout << "Enemy Hit Points: " << hitPoints << endl;
		cout << "- - - - - - -" << endl;
	}
};

// Room TYPE enum: determines the type of room.
enum TYPE{Trap, Nothing, Puzzle, Gold, Key, Start, Exit};
	    //  0       1      2       3    4     5      6

// Room Struct!
// Has a TYPE and if it has been explored or not.
struct Room
{
	TYPE type;
	bool explored; // False/0: Unexplored True/1: Explored
};

// Time to include our external variables, and our prototypes.
extern Room maze[5][10];

extern Character player;

void mazeBuilder();
void printMaze(int, int);

// End of important header guard.
#endif