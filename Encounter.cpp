/* Maze Building file, for our maze functions 
 * By: Berkeley Savage/Anthony Nguyen
 * 10/20/2020
*/

#include "Encounter.h"
#include "CharAndRoom.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

using namespace std;

// So we had to make a pointer to our Character, since it was being passed by VALUE,
// and we wanted pass by REFERENCE. Luckily, we knew how to do that.
Character* pPlayer = &player;

// Trap() room function: will randomly select a trap type for the trap room.
// The offset is used with the puzzle room, since puzzle returns an int value,
// we did not want to check for a pit trap and just avoided it.
bool trap(int offset){
	srand(time(NULL));
	bool value = true;
	int trapType = (rand() % 5) + offset;
	if(trapType == 5)
	{
		trapType = 4;
	}
	// Switch numero quatro, for determining the trap.
	switch(trapType){
		case 0:
			value = pitTrap();
			break;
		case 1:
			printFight();
			cout << "A skeleton has come to slay you!" << endl;
			value = fightSkele();
			break;
		case 2:
			printFight();
			cout << "A slime oozes out to get you!" << endl;
			value = fightSlime();
			break;
		case 3:
			printFight();
			cout << "A zombie shambles towards you!" << endl;
			value = fightZombie();
			break;
		case 4:
			value = spikeTrap();
			break;
		default:
			//if you hit this, something has gone terribly wrong
			cout << "Uh-oh, you shouldn't be seeing this" << endl;
	}
	
	// Will only return false if the player falls into a pit trap to be sent back to the start.
	return value;
}

bool pitTrap(){
	//Let the player know they have fallen for the game's (pit)trap card
	printTrap();
	cout << "Oh no! You've come across a pit trap! How will you escape?" << endl;
	cout << "1. Climb around (Strength)" << endl;
	cout << "2. Jump across (Dexterity)" << endl;
	cout << "3. Search for another path (Intelligence)" << endl;
	int option = 0;
	cin >> option;
	system("CLS");
	
	// Switch 5! For choosing the different ability checks. Yeah, I inlcuded checks like ya said to.
	// However, our checks are based on a 1d10, where above a 5 is a success.
	switch(option){
		// STR
		case 1:
		{
			int roll = (rand() % 10) + pPlayer->str;
			if(roll >= 5){
				cout << "All that time benching handmaidens have proven successful! You climb out of the pit with ease." << endl;
				return true;
			}
			else{
				cout << "Your strength fails you, and you tumble into the pit." << endl;
				return false;
			}
				break;
		}
		// DEX
		case 2:
		{
			int roll = (rand() % 10) + pPlayer->dex;
			if(roll >= 5){
				cout << "With a running start, you leap over the pit and stick the landing on the other side!" << endl;
				return true;
			}
			else{
				cout << "Your foot slips as you went to jump, and you can't catch yourself as you fall into the pit." << endl;
				return false;
			}
				break;
		}
		// INTL -> We had to make Intelligence "Intl" since it couldn't be "Int" for... obvious reasons.
		case 3:
		{
			int roll = (rand() % 10) + pPlayer->intl;
			if(roll >= 5){
				cout << "Eureka! There's an alternate path around the pit to the right. You made it across!" << endl;
				return true;
			}
			else{
				cout << "Maybe there's a path at the bottom of the pit, you think. You decide to investigate, and fall in." << endl;
				return false;
			}
				break;
		}
		default:
			// And if you enter in something that ISN'T an option, you fall anyways. Sucks to suck.
			cout << "Yikes, that wasn't an option. You fall into the pit." << endl;
			return false;
	}
}

// Our next 3 traps are all fights, with different enemies.
// The skeleton deals the most (potential) damage
// The zombie has the most health (which is a little backwards, I have to admit. They're already dead...)
// The slime... is just kinda there. Does the least amount of (potential) damage and has the least health.
// Poor slime man.

// Skeleton fight function. Creates a skeleton character and fights the player.
bool fightSkele(){
	Character skele;
	skele.name = getName();
	skele.status = 1;
	skele.str = 7;
	skele.gold = 15;
	skele.hitPoints = 15;
	
	// Yeah, I made this art myself. Thank you.
	skele.art[0] = "       ________           ";
	skele.art[1] = "      /        \\           ";
	skele.art[2] = "     |   *   *  |          ";
	skele.art[3] = "      >    V   <           ";
	skele.art[4] = "       \\      /            ";
	skele.art[5] = "        |wwww|             ";
	
	fight(skele);
	
	return true;
}

// Slime fight function. Creates a slime character and fights the player.
bool fightSlime(){
	
	Character slime;
	slime.name = getName();
	slime.status = 1;
	slime.gold = 5;
	slime.str = 1;
	slime.hitPoints = 10;
	
	// Yeah, I made this art myself. Thank you.
	slime.art[0] = "            _______          ";
	slime.art[1] = "       ____/        \\__       ";
	slime.art[2] = "      /                \\      ";
	slime.art[3] = "     |     ^      ^     |     ";
	slime.art[4] = "      \\__    \\__/     _/      ";
	slime.art[5] = "         \\___________/        ";
	
	fight(slime);
	
	return true;
}

// Zombie fight function. Creates a zombie character and fights the player.
bool fightZombie(){
	Character zombie;
	zombie.name = getName() ;
	zombie.status = 1;
	zombie.gold = 10;
	zombie.str = 4;
	zombie.hitPoints = 20;
	
	// Yeah, I made this art myself. Thank you.
	zombie.art[0] = "        ________          ";
	zombie.art[1] = "       /     \\##\\         ";
	zombie.art[2] = "     C|  X   |X##|        ";
	zombie.art[3] = "      |    __ \\##|        ";
	zombie.art[4] = "       \\_______\\/         ";
	zombie.art[5] = "         |    |           ";
	
	fight(zombie);
	
	return true;
}

// Our last kind of trap, the spike trap!
// You can't avoid this one lol.
bool spikeTrap(){
	printTrap();
	cout << "Uh oh! You fell in a spike trap!" << endl;
	int damageTaken = (rand() % 10) + 5;
	pPlayer->hitPoints-= damageTaken;
	if(pPlayer->hitPoints <= 0){
		pPlayer->status = 0;
	}
	else{
		// And you can see here, with our pointer to character we used member select to
		// access the hitPoints! This will happen many, many more times.
		cout << "Your current hit points is now: " << pPlayer->hitPoints << endl;	
	}
	return true;
}

// Our fighting function! A lot of this drew inspiration from the previous lab/assignment,
// Battle Sequence. It works similarly (player goes first, then enemy), but we revamped it for
// the different choices to fight.
void fight(Character enemy){
	// We need dodges and stun for later...
	int dodges = 0;
	bool stun = false;
	
	// FIGHT START!
	cout << "The fight has begun!" << endl;
	// Let's make sure our combatants are alive.
	while(pPlayer->status == 1 && enemy.status == 1){
		// hitVal is calculated for each case and used to, well, hit the enemy. Shocker, I know.
		int hitVal = 0;
		// Fight choice for our swtich statement (yes, there IS another one).
		int fightChoice = 0;
		
		// Remember that printArt() statement from Character? Here it is!
		enemy.printArt();
		
		// Options time!
		cout << "It's your turn to act! Do you want to:" << endl;
		cout << "1. Fight the enemy (Strength)" << endl;
		cout << "2. Dodge the incoming attack (Dexterity)" << endl;
		cout << "3. Cast a spell (Intelligence)" << endl;
		cin >> fightChoice;
		system("CLS");
		switch(fightChoice){
			// STR
			case 1:
				// We wanted each attack method to have a little, how you do say it, pizzazz?
				// For Strength, not only does your attack do more base damage (+3 vs. +1 for other attacks),
				// but it also has a chance to crit, dealing double damage.
				// You get a crit if your 1d10 + Strength is greater than 9 (so crit on 9 or 10).
				cout << "Sword in hand, you swing at your enemy!" << endl;
				if(((rand() % 10) + 1 + pPlayer->str) >= 9)
				{
					cout << "Critical strike! You deal double damage!" << endl;
					hitVal = ((rand() % 10) + 3 + pPlayer->str); // Damage will be 1d10 + 2 + Strength
					hitVal = hitVal*2; // We make sure to double the damage here, since this is the CRITICAL.
				}
				else
				{
					hitVal = (rand() % 10) + 3 + pPlayer->str; // Damage will be 1d10 + 2 + Strength
				}
				enemy.hitPoints -= hitVal;
				cout << "A successful strike! You attacked the enemy for " << hitVal << " damage!" << endl;
				// Check if the enemy is dead.
				if(enemy.hitPoints <= 0){
					enemy.status = 0;
				}
				// If not dead, the enemy attacks with Strength
				if(enemy.status==1){
					hitVal = enemy.str + (rand() % 5); // Damage will be 0-4 + enemy strength (since no enemy has a negative strength).
					pPlayer->hitPoints -=hitVal;
					cout << enemy.name << " strikes back at you, dealing " << hitVal << " damage!" << endl;
					cout << "Your current hit points is now: " << pPlayer->hitPoints << endl;
				}
				// Is our player dead? If so, set status to dead.
				if(pPlayer->hitPoints <= 0){
					pPlayer->status = 0;
				}
				break;
			// DEX
			case 2:
				if(dodges < 2)
				{
					// As mentioned here, if you successfully dodge 3 times, you just escape the fight.
					cout << "You go to dodge the enemies attack! If you dodge successfully 3 times, you can escape the fight!" << endl;
					hitVal = (rand() % 10) + 1  + pPlayer->dex; // Chance is 1d10 + Dex
					if(hitVal >= 7) // Must be 7 or greater, to allow for a chance to dodge 3 times 
					{
						cout << "You nimbly avoid the incoming attack!" << endl;
						dodges++;
					}
					else{
						cout << "You attempt to fake left, but the enemy sees right through your lies!" << endl;
						hitVal = enemy.str + (rand() % 5); // Damage will be 0-4 + enemy strength
						pPlayer->hitPoints -=hitVal;
						cout << enemy.name << " has attacked you for " << hitVal << " damage!" << endl;
						cout << "Your current hit points is now: " << pPlayer->hitPoints << endl;
						// Is our player dead? If so, set status to dead.
						if(pPlayer->hitPoints <= 0){
							pPlayer->status = 0;
						}
					}
				}
				else
				{
					// With successful dodges, you leave!
					cout << "You've escaped the fight!" << endl;
					enemy.status = 0;
				}
				break;
			// INT
			case 3:
				// With Intelligence, you cast a spell! The spell itself does a little damage, but it has a
				// chance to STUN an enemy, making them not take their turn. Less damage than strength, but nice
				// not taking any damage.
				cout << "You chant words in a mystical language, and prepare your spell!" << endl;
				hitVal = (rand() % 5) + 3 + pPlayer->intl; // Damage will be 1d10 + 2 + Intl
				enemy.hitPoints -= hitVal;
				cout << "A burst of flame leaps from your hands, and roasts your enemy for " << hitVal << " damage!" << endl;
				// Check if the enemy is dead.
				if(enemy.hitPoints <= 0){
					enemy.status = 0;
				}
				
				if(((rand() % 10) + 1 + pPlayer->intl) >= 9)
				{
					stun = true;
				}
				// If stunned, enemy doesn't attack.
				if(stun)
				{
					cout << enemy.name << " has been stunned by your spell!" << endl;
				}
				// If not dead, the enemy attacks with Strength
				else
				{
					if(enemy.status==1)
					{
						hitVal = enemy.str + (rand() % 5); // Damage will be 1 to the str of the enemy
						pPlayer->hitPoints -=hitVal;
						cout << enemy.name << " ignores the flames and strikes, doing " << hitVal << " damage!" << endl;
						cout << "Your current hit points is now: " << pPlayer->hitPoints << endl;
					}
				}
				// Is our player dead? If so, set status to dead.
				if(pPlayer->hitPoints <= 0){
					pPlayer->status = 0;
				}
				break;
				default: 
					// Default message if you don't know how to follow the instructions.
					cout << "That was not an option, please chose correctly." << endl;
		}
	}
	// Declare winner of the fight
	if(pPlayer->status == 1){
		int goldCollected = gold(enemy.gold);
		cout << pPlayer->name << " has defeated the enemy, Huzzah!" << endl;
		// Player picks up enemy gold after winning the fight
		cout << "You've earned " << goldCollected << " gold!" << endl;
		pPlayer->gold += goldCollected;
	}
	else{
		// Prints if enemy kills the player.
		cout << enemy.name << " proved to be too strong, and slays the hero!" << endl;
	}
}

// Nothing function, which actually does something. Funny how that works.
void nothing()
{
	srand(time(NULL));
	// If our player has under half HP, it will call this function and the player finds a potion
	cout << "Strange, someone has left a health potion lying on the floor. It'd be a shame not to use it..." << endl;
	int hpRecovered = (rand() % 10) + 6; // random number 5-15
	pPlayer->hitPoints+=hpRecovered;
	cout << "You've recovered " << hpRecovered << " hit points!" << endl;
}

// Puzzle function! Calls a question, and prompts player to answer. If right, get gold!
// If wrong though... you get a trap!
int puzzle()
{
	printPuzzle();
	int num = 0;
	// Get question
	// Take in answer
	// Compare
	// Right? Gold!
	// Wrong? Trap!
	Question q = getQuestion();
	q.printQ();
	int guess = 0;
	cin >> guess;
	system("CLS");
	if(guess == q.answer)
	{
		num = gold(15);
		cout << "You answered the question correctly!" << endl;
		cout << "Here is " << num << " gold pieces!" << endl;
		return num;
	}
	else
	{
		cout << "That answer was wrong!" << endl;
		trap(1);
	}
	
	return num;
}

// Gold function! I included an int val in the function call, since I wanted more gold for
// riskier achievements (i.e. answering a question right, defeating an enemy), and basic gold 
//for just finding some in a room.
int gold(int val)
{
	srand(time(NULL));
	system("CLS");
	int gold = (rand() % 20) + 1; // Our random gold will be 1-20;
	gold+=val;
	return gold;
}

// getName() function. Honestly, one of my favorites.
// Randomly generates a name from our lists and returns that value.
// Is called in the creation of our enemies.
string getName()
{	
	srand(time(NULL));
	
	string name = "";
	
	string name1[] = {"Bob", "Sephiroth", "Maverick", "Lord", "Steve"};
	string name2[] = {"'Crazy Hands'", "", "'The Bamboozler'", "'Destructo'", ""};
	string name3[] = {"Skullcrusher", "Mcgee", "Everdark", "Magekiller", "Dragoncaster"};
	
	string n1 = name1[rand()%5];
	string n2 = name2[rand()%5];
	string n3 = name3[rand()%5];
	
	name = n1 + " " + n2 + " " + n3;
	
	return name;
}

// getQuestion() function. Will return a question selected randomly.
// Yes, I pulled all of these questions from your reading quizzes. Better get them right!
Question getQuestion()
{
	srand(time(NULL));
	
	Question q;
	
	// Switch number 6! Don't worry, this is the last one, I promise.
	switch(rand()%10) // Random number 0-9
	{
		case 0:
			q.question[0] = "Which is the insertion operator?";
			q.question[1] = "1. <";
			q.question[2] = "2. <<";
			q.question[3] = "3. >>";
			q.question[4] = "4. >";
			q.answer = 2;
			break;
		case 1:
			q.question[0] = "A C-String is...";
			q.question[1] = "1. I think it's a weapon in WOW";
			q.question[2] = "2. A series of characters as an object of a class";
			q.question[3] = "3. A character array";
			q.question[4] = "4. A null terminated character array";
			q.answer = 4;
			break;
		case 2:
			q.question[0] = "Boolean values in C++ are stored as:";
			q.question[1] = "1. int values";
			q.question[2] = "2. bit values";
			q.question[3] = "3. double values";
			q.question[4] = "4. 'true' or 'false'";
			q.answer = 1;
			break;
		case 3:
			q.question[0] = "Which provides compile or runtime constant declaration?";
			q.question[1] = "1. const";
			q.question[2] = "2. constexpr";
			q.question[3] = "3. constant";
			q.question[4] = "4. cow";
			q.answer = 1;
			break;
		case 4:
			q.question[0] = "How does enum store its data?";
			q.question[1] = "1. double";
			q.question[2] = "2. strings";
			q.question[3] = "3. int";
			q.question[4] = "4. it doesn't";
			q.answer = 3;
			break;
		case 5:
			q.question[0] = "Which command will terminate the entire program and return an error code to the OS?";
			q.question[1] = "1. break";
			q.question[2] = "2. continue";
			q.question[3] = "3. return";
			q.question[4] = "4. exit";
			q.answer = 4;
			break;
		case 6:
			q.question[0] = "Which command terminates the current funciton and returns control flow to the calling function?";
			q.question[1] = "1. break";
			q.question[2] = "2. continue";
			q.question[3] = "3. return";
			q.question[4] = "4. exit";
			q.answer = 3;
			break;
		case 7:
			q.question[0] = "Which is the extraction operator?";
			q.question[1] = "1. <";
			q.question[2] = "2. <<";
			q.question[3] = "3. >>";
			q.question[4] = "4. >";
			q.answer = 3;
			break;
		case 8:
			q.question[0] = "How many bytes would the C-String 'Fallout 4' have?";
			q.question[1] = "1. 10";
			q.question[2] = "2. 9";
			q.question[3] = "3. 11";
			q.question[4] = "4. 8";
			q.answer = 1;
			break;
		case 9:
			q.question[0] = "What is a standard C++ string?";
			q.question[1] = "1. a null terminated character array";
			q.question[2] = "2. series of characters as an object of a class";
			q.question[3] = "3. a character array";
			q.question[4] = "4. a mod in Fallout 4";
			q.answer = 2;
			break;
		default:
			cout << "Uh oh, getQuestion() went wrong." << endl;
	}
	
	return q;
}

// Here is where we store the functions to print out the fancy ASCII lettering!
// Shout out to http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
// That's the site that provided the text.
void printFight()
{
	cout << "___________.___  ________  ___ ______________._." << endl;
	cout << "\\_   _____/|   |/  _____/ /   |   \\__    ___/| |" << endl;
	cout << " |    __)  |   /   \\  ___/    ~    \\|    |   | |" << endl;
	cout << " |     \\   |   \\    \\_\\  \\    Y    /|    |    \\|" << endl;
	cout << " \\___  /   |___|\\______  /\\___|_  / |____|    __" << endl;
	cout << "     \\/                \\/       \\/            \\/" << endl;
}

void printTrap()
{
	cout << "_____________________    _____ __________._." << endl;
	cout << "\\__    ___/\\______   \\  /  _  \\\\______   \\ |" << endl;
	cout << "  |    |    |       _/ /  /_\\  \\|     ___/ |" << endl;
	cout << "  |    |    |    |   \\/    |    \\    |    \\|" << endl;
	cout << "  |____|    |____|_  /\\____|__  /____|    __" << endl;
	cout << "                   \\/         \\/          \\/" << endl;
}

void printPuzzle()
{
	cout << "__________ ____ _______________________.____     ___________._." << endl;
	cout << "\\______   \\    |   \\____    /\\____    /|    |    \\_   _____/| |" << endl;
	cout << " |     ___/    |   / /     /   /     / |    |     |    __)_ | |" << endl;
	cout << " |    |   |    |  / /     /_  /     /_ |    |___  |        \\ \\|" << endl;
	cout << " |____|   |______/ /_______ \\/_______ \\|_______ \\/_______  / __" << endl;
	cout << "                           \\/        \\/        \\/        \\/  \\/" << endl;
}