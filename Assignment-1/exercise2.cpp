//checksum = sum of a number's digits but every second digit is doubled 
//and sumed (if needed) and then added to the checksum.

#include <iostream>
#include <ctime>
#include <cstdlib>

static const int TESTS = 15;

unsigned int checksum(unsigned int num) {
    int digit;
    unsigned int sum = 0;
    bool flag = 1;

  //don't need to cover case for num=0. because sum is initialized 0 so the function will return 0. 
    while (num != 0) {
        if (flag == 1) {
            digit = num % 10;
            sum += digit;
            num = num / 10;
            flag = 0;

        }
        else { 
            digit = 2 * (num % 10);
            if (digit > 9) {
                int newDigit;
                while (digit != 0) {
                    newDigit = digit % 10;
                    sum += newDigit;
                    digit = digit / 10;
                }
            }
            else 
                sum += digit;

            num = num / 10;
            flag = 1;
        }
    }
    return sum;
}

int main()
{
    unsigned int csum = 0;
    unsigned int num_tb[TESTS];
    std::srand(std::time(NULL));

    //random inputs to test our function
    for (int i = 0; i < TESTS; ++i) {
        num_tb[i] = std::rand() % 1000;
        std::cout << num_tb[i] << "   ";
    }
    std::cout << "\n";
    for (int j = 0; j < TESTS; ++j) {
        csum = checksum(num_tb[j]);
        std::cout << csum << "   ";
    }
}