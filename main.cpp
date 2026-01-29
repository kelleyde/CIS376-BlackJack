#include "deck.h"
#include <iostream>
#include <vector>


int main(int argc, char** argv){
	// Mr. W's code
	// Create a deck
	// Deck deck;
	// // Shuffle the deck (notice the static-method call)
	// Deck::shuffle(deck);
	// Auto keyword deduces type for us, so we don't have to.  Here
	// it is for creating an iterator.
	// for(auto it = deck.begin(); it != deck.end(); ++it){
	// 	std::cout << *it << "\t";
	// }
	// std::cout << std::endl;
	
	std::string user_input; // stores user input
	int money = 100; // amount of money user has in game
	bool start;

	// outer game loop, start/restart game
	// int start = true; 
	do {
	// std::cout << "Start Game" << std::endl;
	// std::cout << "How much would you like to bet: ";
	unsigned int betMoney; // amount of money user would like to bet
	// std::cin >> betMoney;
	// std::cout << "You bet "<< betMoney <<"$" << std::endl;
	// check to make sure input is an integer, non-negative, and not greater than the current money they have

	// deck and cards setup
	Deck deck;
	Deck::shuffle(deck);
	int deal_num = 0; // which card of the deck we are on
	// Help create vectors https://www.geeksforgeeks.org/cpp/initialize-a-vector-in-cpp-different-ways/
	std::vector<Card> playerHand = {deck[0], deck[1]};
	std::vector<Card> dealerHand = {deck[2], deck[3]};
	int playerPoints = 0;
	int dealerPoints = 0;

	// deal cards
	for(auto i : playerHand){
		playerPoints = playerPoints + Card::getNumber(i);
		std::cout << i << std::endl;
	}
	std::cout << "Your Points: " << playerPoints << std::endl;

	for(auto i : dealerHand){
		dealerPoints = dealerPoints + Card::getNumber(i);
	}
	std::cout << "Dealer's Card: " << dealerHand[0] << std::endl;

	deal_num = deal_num + 4;

	bool run = true; // run game play loop

	// check for black jack. Points = 21 or Ace and a 10
	if (playerPoints == 21) {
		if (dealerPoints == 21) {
			std::cout << "Double Black Jack Tie" << std::endl;
		}
		else {
			std::cout << "Black Jack! You Win!" << std::endl;
		}
		run = false;
	}

	if (Card::getNumber(playerHand[0]) == 1 or Card::getNumber(playerHand[1]) == 1) {
		if(Card::getNumber(playerHand[0]) == 10 or Card::getNumber(playerHand[1]) == 10) {
			std::cout << "Black Jack! You Win!" << std::endl;
			run = false;
		}
	}
	
	// Game play loop. If player types quit loop exits.
	while(run) {
		if(playerPoints > 21){
				std::cout << "You Bust, You Lose" << std::endl;
				break;
				// insert play again statement and continue,take out i = i-1;
			}
		
		// keep your hand
		if (user_input == "stand") {
			//reveal dealer's points, compare who is closer to 21
			std::cout << "Dealer's Hole Card: " << dealerHand[1] << std::endl;
			std::cout << "Dealer's Points: " << dealerPoints << std::endl;

			// dealer game loop
			while(true){
				// break if dealer points > 17 and dealer points > player points.
				if(dealerPoints > 17 and dealerPoints > playerPoints) {
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
				// go to play again
				break;
			}
				
			if(dealerPoints > playerPoints){
				std::cout << "Player Points: " << playerPoints << " < " 
				<< "Dealer Points: " << dealerPoints << std::endl;
				std::cout << "Dealer Wins, You Lose" << std::endl;
				// go to play again
				break;
			}

			if(dealerPoints < playerPoints){
				std::cout << "Player Points: " << playerPoints << " > " 
				<< "Dealer Points: " << dealerPoints << std::endl;
				std::cout << "You Win, Dealer Loses" << std::endl;
				// go to play again
				break;
			}

			if(dealerPoints == playerPoints){
				std::cout << "Player Points: " << playerPoints << " = " 
				<< "Dealer Points: " << dealerPoints << std::endl;
				std::cout << "Tie" << std::endl;
				// go to play again
				break;
			}
		} // if (stand)

		std::cout << "Your move: ";
		// code from https://stackoverflow.com/questions/5838711/stdcin-input-with-spaces
		// getline allows for spaces to be in the string user_input
		std::getline(std::cin, user_input);
		// convert user_input to lowercase
		// code from https://stackoverflow.com/questions/26202113/how-to-make-case-sensitivity-not-matter-when-inputting-an-answer 
		for (auto i = user_input.begin(); i < user_input.end(); i ++) {
			*i = tolower(*i);
		}
		
		// take another card
		if (user_input == "hit") {
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
			// take a cards at the top of the deck and double bet
			playerHand.push_back(deck[deal_num]);
			std::cout << deck[deal_num] << std::endl;
			// add to points
			playerPoints = playerPoints + Card::getNumber(deck[deal_num]);
			std::cout << "Your Points: " << playerPoints << std::endl;
			
			// deal num increment
			deal_num ++;
			// bet doubles, print bet
			betMoney = betMoney * 2;
			std::cout << "Betting, " << betMoney << "$" << std::endl;
			
			// go to stand
			user_input = "stand";
			// std::cout << user_input << std::endl;
		}

		if (user_input == "quit") {
			run = false;
			// break;
		}

	} // while(run) inner while loop

		if (user_input == "quit"){
			break;
		}

		if (money == 0) {
			std::cout << "You went bankrupt, 0$" << std::endl;
			break;
		}

		std::cout << "Would you like to play again? Yes or No ->  ";
		std::getline(std::cin, user_input);		
		// std::cout << std::endl;

		if (user_input == "No" or user_input == "no"){
			std::cout << "You ended the game.\nEnding balance: " << money << "$" << std::endl;
			start = false;
		}
		else if (user_input == "Yes" or user_input == "yes"){
			start = true;
			// std::cout << "Retype response. Yes or No ->  ";
			// std::cin >> user_input;
		}

	} while(start); // outer while loop

  } //main
