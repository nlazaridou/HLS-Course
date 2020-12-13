// multiply an input number with a num in CSD representation

#include <iostream>
#include <ac_int.h> 
#include <ac_channel.h>
#include <ctime>
#include <cstdlib>

static const int TESTS = 10;
static const int W = 10;

typedef ac_int <W, true> inputType;
typedef ac_int <W+W, true> outputType;


template <int W>
void csd_encode(ac_int<W, true>& num, ac_int<W, false>& x_p, ac_int<W, false>
    & x_m) {
    // num is the input number to be encoded in CSD
    // x_p and x_m are the two bit vectors that represent the CSD number
    int i = 0;
    bool carry = 0;
    bool nextBit, currentBit;

    while (i < W) {
        if (i == W - 1) nextBit = 0;
        else nextBit = num[i + 1];

        currentBit = num[i];

        if (carry == 0) {
            if (currentBit == 0) {
                x_p[i] = 0;
                x_m[i] = 0;
            }
            else if (nextBit == 0 && currentBit == 1) {
                x_p[i] = 1;
                x_m[i] = 0;
            }
            else {
                x_p[i] = 0;
                x_m[i] = 1;
                carry = 1;
            }
            i++;
        }

        else { //carry=1
            if (currentBit==1) {
                x_p[i] = 0;
                x_m[i] = 0;
            }
            else if (nextBit == 0 && currentBit == 0) {
                x_p[i] = 1;
                x_m[i] = 0;
                carry = 0;
            }
            else {
                x_p[i] = 0;
                x_m[i] = 1;
            }
            i++;
        }
    }    
}


outputType csd_mult(inputType& in, ac_int<W, false>& x_p, ac_int<W, false>& x_m) {
    // in is the input value (non constant)
    // x_p and x_m is the CSD representation of a constant
    outputType res = 0;
    int i = 0;
    while (i < W) {
        if (x_p[i]) {
            res = res + (in << i);
        }
        else if (x_m[i]) {
            res = res - (in << i);
        }
        i++;
    }
    return res;
}

int main()
{
    inputType num;
    ac_int<W, false> xp = 0; //positive 1bits
    ac_int<W, false> xm = 0; //negative 1bits
    inputType in;
    outputType mul;

    //two channels for the inputs num and in
    ac_channel<inputType> num_stream;
    ac_channel<inputType> in_stream;

    std::srand(std::time(NULL));

    //filling the input channels with test values in range: (-20) - 20
    for (int i = 0; i < TESTS; ++i)
    {     
        num_stream.write((std::rand() % 41) - 20);
        in_stream.write((std::rand() % 41) - 20);
    }

    while (num_stream.available(1)) {
        num = num_stream.read();
        in = in_stream.read();
        csd_encode<W>(num, xp, xm);
        mul = csd_mult(in, xp, xm);
        std::cout << num << " * " << in << " = " << mul << std::endl;
    }

    return 0;
}

