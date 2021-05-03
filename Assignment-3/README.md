## 3rd Programming Assignment


### Exercise 1

Redo exercise 3 of the 2nd Assignment that refers to the run length encoder design. This time you want the channel to have one new value available at most. This means that your circuit should remember the last value it read each time as well as how many times it read it until then. Avoid using static variables and store the necessary information as private variables of a class according to the following code:
    
    typedef ac_int<4,false> dtype;
    
    class RunLengthEncoder { 
    private:
	    // internal state
    public: 
	    // constructor - init internal state 
	    RunLengthEncoder() {...} 
	    // top-level interface 
	    void run (ac_channel &in, ac_channel &out) {...} 
    };
    

Don't forget to adjust the testing code for the new circuit.

### Exercise 2

You want to design a hardware module in C++ that checks the result of a simplified Blackjack game. The new cards (4-bit unsigned integers) are "opened" in each round of the game through an input channel. The Blackjack calculator sums the values of the cards and calculates the current result. 
Rules:

 - Cards 2-10 count as their natural value.
 - Aces are valued as 11. 
 - There aren't any face cards in our game (jacks, queens, kings)
 - The player **wins**  if the cards he got have a total sum of 21. 
 - If the player exceeds a sum of 21 ("bursts"), he **loses**.
 - The only case where the player **wins** although the sum exceeds 21 is to have 2 aces in the first 2 cards he got.
 - When the player wins or bursts the round stops. The player that hasn't won or burst can keep taking new cards.
 - If the player gets to 5 cards that still have a sum <21, he is considered a **winner**. Each round can't consist of more that 5 cards. 

The calculator returns the game result through two variables `end_round` and `win`. `end_round = true` means the round is over (either because the player won or lost). At the same time `win` indicates wether the player won or lost. 
Implement the Blackjack calculator in the following class
    
    typedef ac_int<4,false> Card;
    
    class BlackJack{ 
    private:
	    // internal state
    public: 
	    // constructor - init internal state 
	    // top-level interface 
	    void run (ac_channel<Card> &in_card,
				    bool &end_round,
				    bool &win) {...}
	    };
    
