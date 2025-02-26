#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

class Blackjack {
private:

    vector<int> shoe;
    int cardsRemaining;
    int wins;
    int losses;
    int pushes;
    int playerMoney;
    int dealerCard1;
    int playerTotal;

    //super 3d vector for results 

    vector<vector<vector<int>>> results;

    //shuffling shoe using a random seed so cards aren't the same every time
    void shuffleShoe() {
        shuffle(shoe.begin(), shoe.end(), default_random_engine(random_device()()));

        cardsRemaining = shoe.size();
    }

public:
    //initializing 6 decks that include 52 cards, then filling it
    Blackjack() {
        shoe.reserve(6 * 52);
        refillShoe();
        playerMoney;
    }

    //part 1 making the new shoe with the decks (aces are 11s)

    void refillShoe() {

        shoe.clear();
        vector<int> deck1{ 2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11 };
        vector<int> deck2{ 2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11 };
        vector<int> deck3{ 2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11 };
        vector<int> deck4{ 2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11 };
        vector<int> deck5{ 2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11 };
        vector<int> deck6{ 2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11 };
        shoe.insert(shoe.end(), deck1.begin(), deck1.end());
        shoe.insert(shoe.end(), deck2.begin(), deck2.end());
        shoe.insert(shoe.end(), deck3.begin(), deck3.end());
        shoe.insert(shoe.end(), deck4.begin(), deck4.end());
        shoe.insert(shoe.end(), deck5.begin(), deck5.end());
        shoe.insert(shoe.end(), deck6.begin(), deck6.end());
        shuffleShoe();



    }

    // part 1 - Blackjack classes - use a shoe of 6 decks of cards, and shuffle the shoe if the card count gets < 100 reshuffle
    int dealCard() {
        if (cardsRemaining < 100) {
            refillShoe();
        }

        int card = shoe.back();
        shoe.pop_back();
        cardsRemaining--;

        return card;
    }

    //only shows output if bool is true or false playGameNoOutput() is false, playGame is true, we don't wanna show output that many times

    void dealInitialCards(int& playerTotal, int& dealerTotal, bool showCards = true) {
        int playerCard1 = dealCard();
        int playerCard2 = dealCard();

        dealerCard1 = dealCard();
        int dealerCard2 = dealCard();

        playerTotal = playerCard1 + playerCard2;
        dealerTotal = dealerCard1 + dealerCard2;

        if (showCards) {
            cout << "Player recieves a " << playerCard1 << " " << playerCard2 << endl;
            cout << "Totaling: " << playerTotal << endl;
            cout << "Dealer shows a " << dealerCard1 << endl;
        }

    }
    // Dealer draws unless their total is 17 or over (dealer stands on 17)

    void dealerTurn() {
        int dealerTotal = dealerCard1;

        while (dealerTotal < 17) {
            int newCard = dealCard();
            dealerTotal += newCard;
        }
    }



    // No outputs until the end, as showing 100,000 would take an insane amount of time. 

   // part 3 - Build a results table to show what strategy loses the least money - for each starting hand value for the player and the dealer, either hit or stand and track the result - just do a single hit or stand and then track win / lose / draw

    // simulate 100, 000 hands, track our starting hand value and then randomly pick hit or stand, and track win / loss / draw result
    void playGameNoOutput() {


        int playerTotal = 0;
        int dealerTotal = 0;
        int bet = 1;

        // Deal first cards
        dealInitialCards(playerTotal, dealerTotal, false);

        int playerInitialHandValue = playerTotal;


        char playerChoice = (rand() % 2 == 0) ? 'h' : 's';
        bool playerStands = (playerChoice == 's');

        //if they have an initial blackjack, auto stand
        if (playerInitialHandValue != 21) {

            if (playerChoice == 'h') {
                int newCard = dealCard();
                playerTotal += newCard;
            }
        }
        else {
            playerStands = true;
        }

        // dealer stands on 17 (draws till 17)
        while (dealerTotal < 17 && playerTotal < 21) {
            int newCard = dealCard();
            dealerTotal += newCard;
        }

        // setting indexes properly to add to vector correctly 
        int dealerIndex = dealerCard1 - 2;
        int playerIndex = playerInitialHandValue - 4;

        if (playerIndex >= 0 && playerIndex < results[dealerIndex].size()) {

            // win condition
            if (playerTotal <= 21 && (playerTotal > dealerTotal || dealerTotal > 21)) {
                if (playerStands) {
                    results[dealerIndex][playerIndex][0]++;
                }
                else {
                    results[dealerIndex][playerIndex][3]++;
                }
                wins++;
                playerMoney += bet;
            }
            // loss conditions
            else if (dealerTotal <= 21 && (dealerTotal > playerTotal || playerTotal > 21)) {

                if (playerStands) {
                    results[dealerIndex][playerIndex][2]++;
                }
                else {
                    results[dealerIndex][playerIndex][5]++;
                }
                losses++;
                playerMoney -= bet;
            }
            // pushes
            else if (dealerTotal == playerTotal) {
                if (playerStands) {
                    results[dealerIndex][playerIndex][1]++;
                }
                else {
                    results[dealerIndex][playerIndex][4]++;
                }
                pushes++;
            }

        }
    }

    //part 2 - Blackjack game using classes and user input - assume every hand is worth $1, tracking win/loss amount


    // players can play it manually this way and track each hand, its value and the dealer's values
    void playGame() {
        playerTotal = 0;
        int dealerTotal = 0;
        int bet = 1;
        int loopCount = 0;

        dealInitialCards(playerTotal, dealerTotal, true);



        if (playerTotal == 21) {

            cout << "BLACKJACK! " << endl;
            wins++;
            playerMoney += bet;
            return;
        }

        char playerChoice;

        cout << "Would you like to hit or stand? (h or s )" << endl;
        cin >> playerChoice;


        while (playerChoice == 'h') {


            int newCard = dealCard();
            playerTotal += newCard;
            cout << "Player hits and receives a " << newCard << endl;
            cout << "New total: " << playerTotal << endl;

            if (playerTotal > 21) {
                cout << "You busted. " << endl;
                break;
            }

            cout << "Would you like to hit or stand? (h or s)" << endl;
            cin >> playerChoice;

        }
        if (playerChoice == 's') {
            cout << "Player stands." << endl;
        }


        while (dealerTotal < 17 && playerTotal < 21) {
            int dealerHiddenCard = dealerTotal - dealerCard1;
            int newCard = dealCard();
            dealerTotal += newCard;

            if (loopCount == 0) {
                cout << "Dealer was hiding a " << dealerHiddenCard << endl;
            }

            cout << "Dealer hits and receives a " << newCard << endl;
            loopCount++;
        }




        if ((playerTotal <= 21 && playerTotal > dealerTotal) || (dealerTotal > 21 && playerTotal <= 21)) {
            int dealerHiddenCard = dealerTotal - dealerCard1;
            if (loopCount == 0) {
                cout << "Dealer was hiding a " << dealerHiddenCard << endl;
            }
            cout << "Dealer has " << dealerTotal << endl;
            cout << "Player wins!" << endl;
            wins++;
            playerMoney += bet;
            loopCount++;
        }
        else if ((dealerTotal <= 21 && dealerTotal > playerTotal) || (playerTotal > 21 && dealerTotal <= 21) || (playerTotal > 21)) {


            int dealerHiddenCard = dealerTotal - dealerCard1;
            if (loopCount == 0) {
                cout << "Dealer was hiding a " << dealerHiddenCard << endl;
            }
            cout << "Dealer has a " << dealerTotal << endl;
            cout << "Dealer wins :(" << endl;

            losses++;
            playerMoney -= bet;
            loopCount++;
        }
        else {
            cout << "Dealer was hiding a " << dealerTotal - dealerCard1 << endl;
            cout << "Push." << endl;

            pushes++;
        }
    }

    // loop then display output for ending
    void loopGame() {

        playGame();
        cout << endl << "Do you want to play another round? (1 for yes, 2 to show the 100,000 simulation or 3 to show results and exit): ";
        int roundChoice;
        cin >> roundChoice;
        if (roundChoice != 1 && roundChoice != 2) {
            displayStats(true);
            return;

        }
        else if (roundChoice == 1) {
            loopGame();
        }
        else if (roundChoice == 2) {
            runManyTimesAndChart();
        }
    }

    // only show balance for long one but show all for short
    void displayStats(bool showWinsAndLosses = false) {



        if (!showWinsAndLosses) {
            cout << "Final player Balance: $" << playerMoney << endl;
        }
        else {
            cout << "Wins: " << wins << endl;
            cout << "Losses: " << losses << endl;
            cout << "Pushes: " << pushes << endl;
            cout << "Final player Balance: $" << playerMoney << endl;
        }
    }

    // loop 100,000 times then output values
    void runManyTimesAndChart() {
        results.assign(10, vector<vector<int>>(18, vector<int>(6, 0)));


        for (int index = 0; index < 100000; ++index) {
            playGameNoOutput();
        }

        //shows balance
        displayStats();

        cout << "Dealer Card:\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11" << endl;
        cout << "Player Hand\t";
        for (int i = 2; i <= 11; ++i) {
            cout << "Stand\tHit\t";
        }
        cout << endl;
        cout << "\t\tW|P|L\tW|P|L\tW|P|L\tW|P|L\tW|P|L\tW|P|L\tW|P|L\tW|P|L\tW|P|L\tW|P|L" << endl;
        for (int i = 0; i < 18; ++i) {
            cout << i + 4 << "\t\t";
            for (int j = 0; j < 10; ++j) {
                int standWins = results[j][i][0];
                int standPushes = results[j][i][1];
                int standLosses = results[j][i][2];
                int hitWins = results[j][i][3];
                int hitPushes = results[j][i][4];
                int hitLosses = results[j][i][5];

                int totalStand = standWins + standPushes + standLosses;
                int totalHit = hitWins + hitPushes + hitLosses;

                cout << standWins << "|" << standPushes << "|" << standLosses << " ";
                cout << hitWins << "|" << hitPushes << "|" << hitLosses << " ";

                wins += standWins + hitWins;
                losses += standLosses + hitLosses;
                pushes += standPushes + hitPushes;

                playerMoney += (standWins + hitWins) - (standLosses + hitLosses);
            }
            cout << endl;
        }

    }


};

