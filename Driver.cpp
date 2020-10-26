/* DUNGEON CRAWLER COMPETITION: Driver
 * By: Berkeley Savage/Anthony Nguyen
 * CS 3700 - Doctor Cantrell
 * 10/20/2020
 *
 * RUBRIC:
 *  - Code Quality: Comment blocks at the top of files, comments throughout explaining things.
 *  - Multiple Files: Driver.cpp, CharAndRoom.h, MazeBuilder.cpp, Encounter.h, and Encounter.cpp
 *  - Functionality: I mean I think we got rid of all the big bugs... we'll see though.
 *  - Enum: TYPE (for type of room in CharAndRoom.h/MazeBuilder.cpp)
 *  - Extern: Maze, Character
 *  - Static: xPos, yPos
 *  - Struct: Character, Room, Question
 *  - Random Number Generation:
 *		- Randomly determine type of room in the maze
 *		- Randomly select the type of trap if trap is activated
 *		- Randomly select names for enemy in fights
 *		- Randomly select questions for puzzle rooms
 *		- Random damage, rolls, checks, etc.
 *		- Random gold given
*/

#include "CharAndRoom.h"
#include "Encounter.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

// Our external Character player. Right now not initialized 
Character player;

int main()
{
	// Build our maze... or I guess I should call it a dungeon, not much of a maze.
	mazeBuilder();
	
	cout << "Welcome to Berkeley and Anthony's Dungeon Crawler!" << endl;
	cout << "You ready to have some fun? Input your answer here: ";
	string input;
	cin >> input;
	system("CLS");
	
	cout << "Choose a hero to traverse this dungeon!" << endl;
	cout << "Your hero is the Player, represented as a P on the map." << endl;
	cout << "Once you've entered the dungeon, you will need a key in order to leave through the exit," << endl;
	cout << "which is denoted by the letter E on your map." << endl;
	cout << "Be cautious adventurer, as there are many things within the dungeon that may prevent you from clearing it!" << endl;
	
	cout << "- - - - - - -" << endl;
	
	// Now that our maze is built, let's start on the characters.
	// 3 presets: Rogue, Fighter, and Wizard
	int choice = 0;
	
	// Shout out to http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
	// That's the site that provided the text.
	cout << "_________   ___ ___    _____ __________    _____  _________________________________________ " << endl;
	cout << "\\_   ___ \\ /   |   \\  /  _  \\\\______   \\  /  _  \\ \\_   ___ \\__    ___/\\_   _____/\\______   \\" << endl;
	cout << "/    \\  \\//    ~    \\/  /_\\  \\|       _/ /  /_\\  \\/    \\  \\/ |    |    |    __)_  |       _/" << endl;
	cout << "\\     \\___\\    Y    /    |    \\    |   \\/    |    \\     \\____|    |    |        \\ |    |   \\" << endl;
	cout << " \\______  /\\___|_  /\\____|__  /____|_  /\\____|__  /\\______  /|____|   /_______  / |____|_  /" << endl;
	cout << "        \\/       \\/         \\/       \\/         \\/        \\/                  \\/         \\/ " << endl;
	cout << "  ____________________.____     _______________________________.___________    _______      " << endl;
	cout << " /   _____/\\_   _____/|    |    \\_   _____/\\_   ___ \\__    ___/|   \\_____  \\   \\      \\     " << endl;
	cout << " \\_____  \\  |    __)_ |    |     |    __)_ /    \\  \\/ |    |   |   |/   |   \\  /   |   \\    " << endl;
	cout << " /        \\ |        \\|    |___  |        \\\\     \\____|    |   |   /    |    \\/    |    \\   " << endl;
	cout << "/_______  //_______  /|_______ \\/_______  / \\______  /|____|   |___\\_______  /\\____|__  /   " << endl;
	cout << "        \\/         \\/         \\/        \\/         \\/                      \\/         \\/    " << endl;
	
	// Ivory is an old character of mine, I love her.
	cout << "1. The human rogue Ivory, who's light on her feet but not likely to win any arm wrestling contests..." << endl;
	cout << "Stats: +2 Dexterity, -2 Strength, +0 Intelligence" << endl << endl;
	
	// Placidus is an old character of Daven's, he's a himbo.
	cout << "2. The dragonborn fighter Placidus, who can lift pretty much anything may not be the sharpest sword in the armory..." << endl;
	cout << "Stats: +0 Dexterity, +2 Strength, -2 Intelligence" << endl << endl;
	
	// Grildor is a character of a friend. I've never played a wizard before so he so graciously allowed
	// me to use Grildor in my program.
	cout << "3. The dwarf wizard Grildor, an incredibly smart mage who has unfortunately stubby legs..." << endl;
	cout << "Stats: -2 Dexterity, +0 Strength, +2 Intelligence" << endl << endl;
	
	cout << "So, who do you chose? Enter the number here: ";
	cin >> choice;
	
	// Switch number 1! Get ready, there's a LOT of switches throught the entire program.
	// Based on user input, switch will set the character to a certain preset.
	// If they input something wrong, the program just ends. Learn how to follow instructions at that point.
	switch(choice)
	{
      case 1:
         player.name = "Ivory the Rogue";
		 player.status = 1;
		 player.str = -2;
		 player.dex = 2;
		 player.intl = 0;
		 player.hitPoints = 50;
		 player.gold = 0;
		 player.key = 0;
         break;
      case 2:
         player.name = "Placidus the Fighter";
		 player.status = 1;
		 player.str = 2;
		 player.dex = 0;
		 player.intl = -2;
		 player.hitPoints = 50;
		 player.gold = 0;
		 player.key = 0;
         break;
      case 3:
         player.name = "Grildor the Wizard";
		 player.status = 1;
		 player.str = 0;
		 player.dex = -2;
		 player.intl = +2;
		 player.hitPoints = 50;
		 player.gold = 0;
		 player.key = 0;
         break;
      default:
         cout << "Invalid choice." << endl;
		 return 1;
	}
	
	cout << "You've selected: " << player.name << "!" << endl;
	cout << "Enter any key to continue. ";
	cin >> input;
	system("CLS");
	
	// Set boolean to use for the while loop. This keeps the dungeon going until the player is
	// dead or they escape!
	bool running = true;
	
	// Dungeon time!
	while(running)
	{
		// We want to save our position so the player can move throughout the map, so
		// we make x and y static as to not override them each time the while loop occurs
		static int xPos = 0;
		static int yPos = 0;
		
		// UI printing for information.
		printMaze(xPos, yPos);
		int move = 0;
		cout << "Where would you like to move?" << endl;
		cout << "1) North" << endl << "2) East" << endl << "3) South" << endl << "4) West" << endl;
		cout << "- - - - - - -" << endl;
		// Moving North: pos {x-1, y}
		// Moving East: pos {x, y+1}
		// Moving South: pos {x+1, y}
		// Moving West: pos {x, y-1}
		cin >> move;
		
		// Hope you weren't tired of switches yet! Switch number 2!
		switch(move)
		{
			case 1:	// NORTH
				 if(xPos - 1 >= 0)
					 xPos-=1;
				 else
					 // Technically the program prints these statements, but the screen clears
					 // too quickly to see them. Oh well.
					 cout << "Cannot go North!" << endl;
				 break;
			case 2: // EAST
				 if(yPos + 1 < 10)
					 yPos+=1;
				 else
					 cout << "Cannot go East!" << endl;
				 break;
			case 3: // SOUTH
				 if(xPos + 1 < 5)
					 xPos+=1;
				 else
					 cout << "Cannot go South!" << endl;
				 break;
			case 4: // WEST
				 if(yPos - 1 >= 0)
					 yPos-=1;
				 else
					 cout << "Cannot go West!" << endl;
				 break;
			case 10:
				// 10 here will cause the program to stop completely. Very nice in the initial
				// testing phase.
				return 1;
				break;
			default:
				 cout << "Invalid choice." << endl;
		}
		
		system("CLS");
		// We have our movement calculated, time to active whatever happens in the next room!
		// SWITCH NUMBER 3!
		if(!maze[xPos][yPos].explored)
		{
			switch(maze[xPos][yPos].type)
			{
				// Trap room: calls the trap() function from Encounter.cpp
				// Will return a boolean, only false if the player is sent back to the start.
				case (TYPE)0:
					 if(trap(0))
					 {
						 // Trap can be combat, so we have to make sure our player is alive.
						 if(player.status == 0)
						 {
							running = false;
						 }
					 }
					 else
					 {
						 if(player.status == 0)
						 {
							running = false;
						 }
						 else
						 {
							xPos = 0;
							yPos = 0;
							cout << "Uh oh! The pit sent you all the way back to the start!" << endl;
						 }
					 }
					 // if False: position set to start
					 break;
				// The "Nothing" room! Unless your health is low, then we give you a health potion.
				// You're welcome.
				case (TYPE)1:
					 if(player.hitPoints > 35)
					 {
						 cout << "Huh, there's nothing here." << endl;
					 }
					 else
					 {
						 nothing();
					 }
					 break;
				// Puzzle room! If answered wrong, it will activate a trap, and right will provide them
				// some wonderful gold. Check for more details in Encounter.cpp.
				case (TYPE)2:
				{
					 cout << "There's a strange question written on the wall. Maybe you should answer it?" << endl;
					 int goldFound = puzzle();
					 player.gold+=goldFound;
					 // returns an int: gold() for gold, 0 for nothing
					 // add gold to player gold
					 break;
				}
				// Gold room! You find some gold. Pretty straight forward.
				case (TYPE)3:
				{
					 int goldFound = gold(0);
					 player.gold+=goldFound;
					 cout << "You found " << goldFound << " pieces of gold!" << endl;
					 break;
				}
				// Key room! The map can have a number of keys, as long as you have one, you can leave the
				// dungeon. So, key is just a boolean we set true/false.
				case (TYPE)4:
					 cout << "Hey, you've found a key! Now you can exit the dungeon!" << endl;
					 player.key = 1;
					 break;
				// Start. It's the start.
				case (TYPE)5:
					 cout << "This is the start of the dungeon." << endl;
					 break;
				// Exit. It's the exit.
				case (TYPE)6:
					 cout << "This is the exit of the dungeon. You can only leave if you have a key." << endl;
					 break;
				// You should never see this text but, just in case it's there for troubleshooting.
				default:
					 cout << "Invalid type." << endl;
			}
			
			// Make sure to set our current room to explored for map printing.
			maze[xPos][yPos].explored = true;
		}
		else
		{
			// If we've already explored a room...
			cout << "It seems you've been here before..." << endl;
		}
		
		if(xPos == 4 && yPos == 9 && player.key)
		{
			// This is how to leave the dungeon! Must be on the exit, and have a key!
			running = false;
		}
	}
	
	system ("CLS");
	if(player.status == 1)
	{
		// Will print if you survived.
		cout << "____   ____._______________________________ _______________.___._." << endl;
		cout << "\\   \\ /   /|   \\_   ___ \\__    ___/\\_____  \\\\______   \\__  |   | |" << endl;
		cout << " \\   Y   / |   /    \\  \\/ |    |    /   |   \\|       _//   |   | |" << endl;
		cout << "  \\     /  |   \\     \\____|    |   /    |    \\    |   \\\\____   |\\|" << endl;
		cout << "   \\___/   |___|\\______  /|____|   \\_______  /____|_  // ______|__" << endl;
		cout << "                       \\/                  \\/       \\/ \\/       \\/" << endl;
		cout << "Hooray, you've escaped the dungeon! You collected " << player.gold << " gold pieces!" << endl;
		cout << "Enter any key to exit: ";
		cin >> input;
		
	}
	else
	{
		// Will print if you died like a loser.
		cout << "________  _________________________________   ________________ " << endl;
		cout << "\\______ \\ \\_   _____/\\_   _____/\\_   _____/  /  _  \\__    ___/ " << endl;
		cout << " |    |  \\ |    __)_  |    __)   |    __)_  /  /_\\  \\|    |    " << endl;
		cout << " |    `   \\|        \\ |     \\    |        \\/    |    \\    |    " << endl;
		cout << "/_______  /_______  / \\___  /   /_______  /\\____|__  /____| /\\ " << endl;
		cout << "        \\/        \\/      \\/            \\/         \\/       \\/ " << endl;
		cout << "Alas, this is the end of our hero's journey. You have failed to escape the dungon and you perished." << endl;
		cout << "Enter any key to exit: ";
		cin >> input;
	}
}