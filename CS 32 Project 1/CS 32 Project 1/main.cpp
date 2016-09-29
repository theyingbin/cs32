// snakepit.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Snake.h"
#include "Pit.h"
#include "Player.h"
#include "globals.h"
#include "Game.h"
using namespace std;


///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
	// Initialize the random number generator.  (You don't need to
	// understand how this works.)
	srand(static_cast<unsigned int>(time(0)));

	// Create a game
	// Use this instead to create a mini-game:   Game g(3, 3, 2);
	Game g(9, 10, 40);

	// Play the game
	g.play();
}

