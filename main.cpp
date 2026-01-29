#include "deck.h"
#include <iostream>
#include <vector>
#include <limits>
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
	unsigned int betMoney; // amount of money user would like to bet - used for validating if betMoney input is an integer
	int i = 1; // indicates if game is running
	int money = 100; // amount of money user starts with in game
	int deal_num = 0; // which card of the deck we are on

	// Card& first_deal = deck[deal_num];
	// std::cout << first_deal << std::endl;

	// int card_num = Card::getNumber(first_deal);
	// std::cout << card_num << std::endl;

	// Start game
	std::cout << "Start Game" << std::endl;
	std::cout << "How much would you like to bet: ";

	while(!(std::cin >> betMoney)){
		// validates that bet money is a valid integer
		std::cout << "That is not an integer. Please enter an integer: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	while(betMoney > money || betMoney < 0){
		// checks that player has enough money to be and also that it is non-negative
		std::cout << "Invalid amount of bet money. How much would you like to bet: ";
		std::cin >> betMoney;
	}

	std::cout << "You bet "<< betMoney <<"$" << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Help create vectors https://www.geeksforgeeks.org/cpp/initialize-a-vector-in-cpp-different-ways/
	std::vector<Card> playerHand = {deck[deal_num], deck[deal_num+1]};
	std::vector<Card> dealerHand = {deck[deal_num+2], deck[deal_num+3]};
	int playerPoints = 0;
	int dealerPoints = 0;
	deal_num = deal_num + 4; // updates place in deck

	for(auto i : playerHand){
		// calculates how many points player has based on their cards
		playerPoints = playerPoints + Card::getNumber(i);
		std::cout << i << std::endl;
	}
	std::cout << "Your Points: " << playerPoints << std::endl;

	for(auto i : dealerHand){
		dealerPoints = dealerPoints + Card::getNumber(i);
	}
	std::cout << "Dealer's Card: " << dealerHand[0] << "[Hole Card Hidden]" << std::endl;

	// Game play loop. If player types quit, loop exits.
	do {
		if(playerPoints > 21){
				std::cout << "You Bust, You Lose" << betMoney << "$" << std::endl;
				money -= betMoney;

				// resets hands
				playerPoints = 0;
				dealerPoints = 0;
				
				playerHand = {deck[deal_num+1], deck[deal_num+2]};
				dealerHand = {deck[deal_num+3], deck[deal_num+4]};
				
				std::cout << "Your Points: " << playerPoints << std::endl;
				std::cout << "Dealer's Card: " << dealerHand[0] << "[Hole Card Hidden]" << std::endl;
			}
		
		std::cout << "Your move: ";
		// code from https://stackoverflow.com/questions/5838711/stdcin-input-with-spaces
		// getline allows for spaces to be in the string user_input
		std::getline(std::cin, user_input);
		// convert user_input to lowercase
		// code from https://stackoverflow.com/questions/26202113/how-to-make-case-sensitivity-not-matter-when-inputting-an-answer 
		for (auto i = user_input.begin(); i < user_input.end(); i ++) {
			*i = tolower(*i);
		}

		// keep your hand
		if (user_input == "stand") {
			//reveal dealer's points, compare who is closer to 21
			std::cout << "Dealer's Hole Card: " << dealerHand[1] << std::endl;
			std::cout << "Dealer's Points: " << dealerPoints << std::endl;

			// dealer game loop
			while(true){

				// break if dealer points > 17 or dealer points > player points.
				if(dealerPoints > 17 || dealerPoints > playerPoints) {
					break;
				}

				// dealer hit
				dealerHand.push_back(deck[deal_num]);
				// add points
				dealerPoints = dealerPoints + Card::getNumber(deck[deal_num]);
				// print
				std::cout << deck[deal_num] << "\tDealer Points:" << dealerPoints << std::endl;
				// increment deal_num
				deal_num ++;
					
				} // while dealer game loop
			
			// if dealer busts
			if(dealerPoints > 21){
				std::cout << "Dealer Bust, You Win" << std::endl;
				money += betMoney;

				// resets hands
				playerPoints = 0;
				dealerPoints = 0;
				
				playerHand = {deck[deal_num+1], deck[deal_num+2]};
				dealerHand = {deck[deal_num+3], deck[deal_num+4]};
				
				std::cout << "Your Points: " << playerPoints << std::endl;
				std::cout << "Dealer's Card: " << dealerHand[0] << "[Hole Card Hidden]" << std::endl;
			}
			
			// win loss conditions
			else {
				if (playerPoints > dealerPoints) {
					std::cout << "You Win!" << std::endl;
					money += betMoney;

					// resets hands
					playerPoints = 0;
					dealerPoints = 0;
					
					playerHand = {deck[deal_num+1], deck[deal_num+2]};
					dealerHand = {deck[deal_num+3], deck[deal_num+4]};
					
					std::cout << "Your Points: " << playerPoints << std::endl;
					std::cout << "Dealer's Card: " << dealerHand[0] << "[Hole Card Hidden]" << std::endl;
					
				} else if (playerPoints < dealerPoints) {
					std::cout << "Dealer Wins." << std::endl;
					money -= betMoney;

					// resets hands
					playerPoints = 0;
					dealerPoints = 0;
					
					playerHand = {deck[deal_num+1], deck[deal_num+2]};
					dealerHand = {deck[deal_num+3], deck[deal_num+4]};
					
					std::cout << "Your Points: " << playerPoints << std::endl;
					std::cout << "Dealer's Card: " << dealerHand[0] << "[Hole Card Hidden]" << std::endl;

				} else {
					std::cout << "It's a Tie." << std::endl;

					// resets hands
					playerPoints = 0;
					dealerPoints = 0;
					
					playerHand = {deck[deal_num+1], deck[deal_num+2]};
					dealerHand = {deck[deal_num+3], deck[deal_num+4]};
					
					std::cout << "Your Points: " << playerPoints << std::endl;
					std::cout << "Dealer's Card: " << dealerHand[0] << "[Hole Card Hidden]" << std::endl;
				}
			}
		}

		if (user_input == "quit") {
			i = i-1;
		}
		
		// take another card
		if (user_input == "hit") {
			// print the card at the top of the Shuffled Deck stack and store the points 
			// push_back adds to a vector
			playerHand.push_back(deck[deal_num]);
			// add points
			playerPoints = playerPoints + Card::getNumber(deck[deal_num]);
			// print
			std::cout << deck[deal_num] << "\tYour Points: " << playerPoints << std::endl;

			// Go to next card
			deal_num ++;
		}

		// double bet, take one more card
		if (user_input == "double down") {
			if(betMoney * 2 > money){
				std::cout << "Not enough money to double down!" << std::endl;
				continue;
			}

			betMoney *= 2;
			std::cout << "Bet doubled" << std::endl;

			// take a cards at the top of the deck and double bet
			playerHand.push_back(deck[deal_num]);
			std::cout << deck[deal_num] << std::endl;
			// add to points
			playerPoints = playerPoints + Card::getNumber(deck[deal_num]);
			std::cout << "Your Points: " << playerPoints << std::endl;
			
			// deal num increment
			deal_num ++;

			if(playerPoints > 21){
				std::cout << "You Bust" << std::endl;
				betMoney -= money;

				// resets hands
				playerPoints = 0;
				dealerPoints = 0;
				
				playerHand = {deck[deal_num+1], deck[deal_num+2]};
				dealerHand = {deck[deal_num+3], deck[deal_num+4]};
				
				std::cout << "Your Points: " << playerPoints << std::endl;
				std::cout << "Dealer's Card: " << dealerHand[0] << "[Hole Card Hidden]" << std::endl;
			}
			
			// go to stand
			user_input = "stand";
			// std::cout << user_input << std::endl;
		}

	} while (i != 0);

	return 0;
  } //main