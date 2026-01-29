#include "deck.h"
#include <iostream>
#include <vector>
// using namespace std;

//Card& deal(int num_cards_dealt){}

int main(int argc, char** argv){
	// Create a deck
	Deck deck;
	// Shuffle the deck (notice the static-method call)
	Deck::shuffle(deck);
	// Auto keyword deduces type for us, so we don't have to.  Here
	// it is for creating an iterator.
	// for(auto it = deck.begin(); it != deck.end(); ++it){
	// 	std::cout << *it << "\t";
	// }
	// std::cout << std::endl;
	
	std::string user_input;
	unsigned int betMoney; // amount of money user would like to bet
	int i = 1; // indicates if game is running
	int money = 100; // amount of money user has in game
	int deal_num = 0; // which card of the deck we are on

	// Card& first_deal = deck[deal_num];
	// std::cout << first_deal << std::endl;

	// int card_num = Card::getNumber(first_deal);
	// std::cout << card_num << std::endl;

	// Start game
	std::cout << "Start Game" << std::endl;
	// std::cout << "How much would you like to bet: ";
	// std::cin >> betMoney;
	// std::cout << "You bet "<< betMoney <<"$" << std::endl;
	// check to make sure input is an integer, non-negative, and not greater than the current money they have

	// Help create vectors https://www.geeksforgeeks.org/cpp/initialize-a-vector-in-cpp-different-ways/
	std::vector<Card> playerHand = {deck[0], deck[1]};
	std::vector<Card> dealerHand = {deck[2], deck[3]};
	int playerPoints = 0;
	int dealerPoints = 0;

	for(auto i : playerHand){
		playerPoints = playerPoints + Card::getNumber(i);
		std::cout << i << std::endl;
	}
	std::cout << "Your Points: " << playerPoints << std::endl;

	for(auto i : dealerHand){
		dealerPoints = dealerPoints + Card::getNumber(i);
	}
	std::cout << "Dealer's Card: " << dealerHand[0] << std::endl;

	deal_num = deal_num +4;

	// Game play loop. If player types quit loop exits.
	// Thinking calling Deck::shuffle(deck) at index 0, but incrementing the index each time the "pull card" function is called
	do {
		// check if playerPoints > 21, if so they lose and int money -= betMoney
		// check if money == 0, if so, force quit game 
		// check if playerPoints == 21, if so they win and int money += betMoney
		std::cout << "Your move: " << user_input << std::endl;
		std::cin >> user_input;
		// convert user_input to lowercase
		// code from 
		// https://stackoverflow.com/questions/26202113/how-to-make-case-sensitivity-not-matter-when-inputting-an-answer 
		for (auto i = user_input.begin(); i < user_input.end(); i ++) {
			*i = tolower(*i);
		}

		if (user_input == "quit") {
			i = i-1;
		}
		
		// take another card
		if (user_input == "hit") {
			// print the card at the top of the Shuffled Deck stack and store the points 
			playerHand.push_back(deck[deal_num]);
			std::cout << deck[deal_num] << std::endl;
			playerPoints = playerPoints + Card::getNumber(deck[deal_num]);
			std::cout << "Your Points: " << playerPoints << std::endl;
			// Go to next card
			deal_num ++;

			// check if player is over 21
			if(playerPoints > 21){
				std::cout << "You Bust" << std::endl;
				i = i - 1;
				// insert play again statement and continue,take out i = i-1;
			}
		}

		// // double bet, take one more card
		// if (user_input == "double down") {
		// 	// return 2 cards at the top of the Shuffled Deck stack and store the points
		// }
		
		// // keep your hand
		// if (user_input == "stand") {
		// 	//reveal dealer's points, compare who is closer to 21

			// Dealer's turn
				// reveal "hole card"
				// if dealerPoints < 17, make them hit
				// if dealerPoints < playerPoints, make them hit
			// Compare playerPoints and dealerPoints, if playerPoints < dealerPoints, player loses. if playerPoints > dealerPoints, player wins. if equal, nothing happens
		// }

		else {
			std::cout << "Retype move: " << std::endl;
		}

	} while (i != 0);

  } //main
