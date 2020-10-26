/* Maze Building file, for our maze functions 
 * By: Berkeley Savage/Anthony Nguyen
 * 10/20/2020
*/

#include "CharAndRoom.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Room maze[5][10];

void mazeBuilder()
{	
	srand(time(NULL));	// Our Random is seeded with the time
	
	int randNum = 0;
	int keys = 0;
	
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			randNum = (rand() % 5); // Our random number will be a number 0-4, corresponding to room type.
			
			if(randNum == 4)
			{
				// I wanted to make keys a little more rare, so we do one more random chance.
				randNum = (rand() % 2) + 3; // Our random number will be 3 or 4
				if(randNum == 4)
				{
					// Let's track if we actually put a key on the map, for later.
					keys++;
				}
			}
			
			maze[i][j].type = (TYPE)randNum;
			maze[i][j].explored = false;
		}
	}
	
	// Here is what the keys variable is for! In the chance no keys spawn (belive me, it can happen),
	// we will automatically set a key in the maze.
	if(keys == 0)
	{
		maze[2][5].type = (TYPE)4; // Yes, I'm just making the middle spot a key. Sue me.
	}
	
	// Now, we do need to override our start and exits, since they do different things
	maze[0][0].type = (TYPE)5;
	maze[0][0].explored = true;
	maze[4][9].type = (TYPE)6;
}

void printMaze(int x, int y)
{
	// printMaze() also prints out our Player information, since it updates each time and is
	// easy to print together.
	cout << "- - - - - - -" << endl;
	cout << "Player Name: " << player.name << endl;
	cout << "Player Hit Points: " << player.hitPoints << endl;
	cout << "Gold Collected: " << player.gold << endl;
	if(player.key)
	{
		cout << "You have a key!" << endl;
	}
	else
	{
		cout << "You don't have a key." << endl;
	}
	cout << "- - - - - - -" << endl;
	
	
	for(int i = 0; i < 5; i++)
	{
		cout << " ";
		for(int k = 0; k < 39; k++)
		{
			cout << "=";
		}
		cout << endl << "|";
		for(int j = 0; j < 10; j++)
		{
			if(i == x && j == y)
			{
				// For current position, it will print a P for Player.
				cout << " P ";
			}
			else if(i == 4 && j == 9)
			{
				// Will print E for our exit.
				cout << " E ";
			}
			else
			{
				if(!maze[i][j].explored)
				{
					// These rooms are unexplored.
					cout << " * ";
				}
				else
				{
					// These rooms are explored.
					cout << " _ ";
				}
			}
			
			cout << "|";
		}
		cout << endl;
	}
	cout << " ";
	for(int i = 0; i < 39; i++)
	{
		cout << "=";
	}
	cout << endl;
	
	cout << "- - - - - - -" << endl;
}