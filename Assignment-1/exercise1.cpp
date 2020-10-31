//cpp program to count 1's of a binary representation of a random unsigned int number (known as set bits)
#include <iostream>
#include <ctime>
#include <cstdlib>

static const int TESTS = 10;

unsigned short int ones_counter(unsigned int input) {
    unsigned short int count = 0;
    while (input != 0) {
        count += input & 1; //input & (000...001) means that we only get 1 if lsb is 1
        input = input >> 1; //and then we remove lsb by shifting right
    }
    return(count);
}

int main()
{
    unsigned short int output=0;
    unsigned int input_tb[TESTS];
    std::srand(std::time(NULL));

    //random inputs to test our function
    for (int i = 0; i < TESTS; ++i) {
        input_tb[i] = std::rand() % 100;
        output = ones_counter(input_tb[i]);
        std::cout << input_tb[i] << " ---> " << output << "\n";
    }
}