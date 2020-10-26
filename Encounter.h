/* Encounters header file, holds question struct and functions
 * By: Berkeley Savage/Anthony Nguyen
 * 10/20/2020
*/

#include <string>
#include "CharAndRoom.h"
#include <iostream>

using namespace std;

// Start of important header guard.
#ifndef ENCOUNTER_H
#define ENCOUNTER_H

// Question Struct!
// Holds the string array of the question itself (determined in Encounter.cpp), and
// the print function to actually print it out.
struct Question
{
	string question[5]; // {"Question", "Answer 1", "Answer 2", "Answer 3", "Answer 4"}
	int answer;
	
	void printQ()
	{
		for(int i = 0; i < 5; i++)
		{
			cout << question[i] << endl;
		}
	}
};

// All of our function prototypes from Encounter.cpp.
// Yes I know there is a lot.
bool trap(int);
bool pitTrap(); // Success: True Fail: False
bool fightSkele();
bool fightSlime();
bool fightZombie();
bool spikeTrap();
void fight(Character);
void nothing();
int puzzle(); // CANNOT PICK PITTRAP
int gold(int);
string getName();
Question getQuestion();
void printFight();
void printTrap();
void printPuzzle();

// End of important header guard.
#endif