#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

#include <ac_int.h>
#include <ac_channel.h>

typedef ac_int<4,false> Card;

class BlackJack {
	private:
		int sumCards;
		int countCards;
		bool oneAceFound;
	public:
	BlackJack(){
		sumCards = 0;
		countCards = 0;
		oneAceFound = false;
	}
	
	void run (ac_channel<Card> &in_card, bool &end_round, bool &win){
		if (in_card.available(1)) {
			Card selectedCard = in_card.read();
			countCards += 1;
			if(selectedCard==1 & countCards<3) { //IF FIRST TWO CARDS ARE ACES
				if(oneAceFound) {
					win = true;
					end_round=true;
				}
				else {
					oneAceFound = true;
					sumCards += 11;
				}
			}
			else { 
				sumCards += selectedCard;
			}

			if (sumCards>20) { //IF SUM IS >=21
				end_round = true;
				if (sumCards==21) {
					win=true;
				}
			}
			else if (countCards==5) { //if AFTER 5 CARDS, sum IS <21 
				win==true;			  //if after 5 cards sum>20 is covered
				end_round=true;
			}
		}
	}
	
	void reset() {
		sumCards = 0;
		countCards = 0;
		oneAceFound = 0;
	}
};

int main() {
	ac_channel<Card> test_deck[9]; //9 decks of cards
	Card test_in_card;
	
	//Test 1: No Cards - - should not end - should not win
	
	//Test 2: Sum 20 - should not end - should not win
	
	test_in_card = 1;
	test_deck[1].write(test_in_card);
	test_in_card = 19;
	test_deck[1].write(test_in_card);
	
	//Test 3: Sum 24 - should end - should not win
	
	test_in_card = 10;
	test_deck[2].write(test_in_card);
	test_in_card = 8;
	test_deck[2].write(test_in_card);
	test_in_card = 6;
	test_deck[2].write(test_in_card);
	
	//Test 4: Sum 21 - should end - should win
	
	test_in_card = 9;
	test_deck[3].write(test_in_card);
	test_in_card = 7;
	test_deck[3].write(test_in_card);
	test_in_card = 5;
	test_deck[3].write(test_in_card);
	
	//Test 5: Sum 21 but Card Count > 5 - should end - should not win
	
	test_in_card = 1;
	test_deck[4].write(test_in_card);
	test_in_card = 2;
	test_deck[4].write(test_in_card);
	test_in_card = 3;
	test_deck[4].write(test_in_card);
	test_in_card = 4;
	test_deck[4].write(test_in_card);
	test_in_card = 5;
	test_deck[4].write(test_in_card);
	test_in_card = 6;
	test_deck[4].write(test_in_card);
	
	// Test 6: Sum > 21 and Card Count > 5 but has 2 aces before - should end - should win
	
	test_in_card = 4;
	test_deck[5].write(test_in_card);
	test_in_card = 1;
	test_deck[5].write(test_in_card);
	test_in_card = 3;
	test_deck[5].write(test_in_card);
	test_in_card = 1;
	test_deck[5].write(test_in_card);
	test_in_card = 5;
	test_deck[5].write(test_in_card);
	test_in_card = 10;
	test_deck[5].write(test_in_card);
	
	// Test 7: Sum > 21 and Card Count > 5 - should end - should not win
	
	test_in_card = 4;
	test_deck[6].write(test_in_card);
	test_in_card = 3;
	test_deck[6].write(test_in_card);
	test_in_card = 3;
	test_deck[6].write(test_in_card);
	test_in_card = 7;
	test_deck[6].write(test_in_card);
	test_in_card = 5;
	test_deck[6].write(test_in_card);
	test_in_card = 10;
	test_deck[6].write(test_in_card);
	
	// Test 8: Card Count > 5 but Sum == 21 before - should end - should win
	
	test_in_card = 4;
	test_deck[7].write(test_in_card);
	test_in_card = 1;
	test_deck[7].write(test_in_card);
	test_in_card = 3;
	test_deck[7].write(test_in_card);
	test_in_card = 1;
	test_deck[7].write(test_in_card);
	test_in_card = 5;
	test_deck[7].write(test_in_card);
	test_in_card = 10;
	test_deck[7].write(test_in_card);
	
	// Test 9: Sum < 21 and 2 aces - should end - should win
	
	test_in_card = 3;
	test_deck[8].write(test_in_card);
	test_in_card = 1;
	test_deck[8].write(test_in_card);
	test_in_card = 4;
	test_deck[8].write(test_in_card);
	test_in_card = 1;
	test_deck[8].write(test_in_card);
	test_in_card = 2;
	
	BlackJack game;
	
	for (int i=0; i<9;i++) {
		bool test_end_round = false;
		bool test_won = false;
		while(test_deck[i].available(1)) {
			game.run(test_deck[i], test_end_round, test_won);
		}
		std::cout <<"Test #"<< i+1 << ":  ||  Round Ended: [" << test_end_round << "]  Round Won: [" << test_won << "]\n";
		game.reset();
	}
	
	return 0;
}
