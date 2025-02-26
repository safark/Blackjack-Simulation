#include "BlackjackContents.h"
using namespace std;

int main() {

	Blackjack game;

	int startChoice = 0;

	cout << "\t\t\t==========================================================================\n";
	cout << "\t\t\t|                                                                        |\n";
	cout << "\t\t\t|                    Welcome to The Safar Casino.                        |\n";
	cout << "\t\t\t|                                                                        |\n";
	cout << "\t\t\t|              Press 1 if you want to play Blackjack.			 |\n";
	cout << "\t\t\t|                                                                        |\n";
	cout << "\t\t\t| Press 2 to simulate 100k hands of BJ and display a table of results.   |\n";
	cout << "\t\t\t|                                                                        |\n";
	cout << "\t\t\t==========================================================================\n";

	cin >> startChoice;



	if (startChoice == 1) {

		//manually play the game
		game.loopGame();



	}
	else {

		//simulate 100,000 hands, track our starting hand value and then randomly pick hit or stand, and track win/loss/draw result
		//Display a table showing the results of hitting and standing for each starting value 

		game.runManyTimesAndChart();

	}






	return 0;
}