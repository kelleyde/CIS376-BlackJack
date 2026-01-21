#include "deck.h"
#include <iostream>

int main(int argc, char** argv){
	// Create a deck
	Deck deck;
	// Shuffle the deck (notice the static-method call)
	Deck::shuffle(deck);
	// Auto keyword deduces type for us, so we don't have to.  Here
	// it is for creating an iterator.
	for(auto it = deck.begin(); it != deck.end(); ++it){
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
	
	std::string user_input;
	int i = 1;
	// Game play loop. If player types quit loop exits.
	do {
		std::cin >> user_input;
		std::cout << "Your input: " << user_input << std::endl;
		// convert user_input to lowercase
		// code from 
		// https://stackoverflow.com/questions/26202113/how-to-make-case-sensitivity-not-matter-when-inputting-an-answer 
		for (auto i = user_input.begin(); i < user_input.end(); i ++) {
			*i = tolower(*i);
		}

		std::cout << "Your lower finput: " << user_input << std::endl;
		if (user_input == "quit") {
		i = i-1;
		}
	} while (i != 0);

}
