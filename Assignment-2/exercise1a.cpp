//a) minimum bitwidth of specific operation
//a*b => 16bits
//c*d => 18bits
//(a*b) + (c*d) = 18 bits (EBITS) so we choose e to be a 18bit value

#include <ac_int.h> 
#include <ac_channel.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

static const int SAMPLES = 20;
static const int EBITS = 18;

typedef ac_int < 8, false> bu; //bit unsigned
typedef ac_int < 9, true> bs;  //bit signed

ac_int<EBITS, true> calculate_e(bu a, bu b, bs c, bs d) {
    ac_int<EBITS, true> e = (a * b) + (c * d);
    return e;
}

//now we need to see if less bits are producing correct results
ac_int<EBITS-1, true> calculate_not_e(bu a, bu b, bs c, bs d) {
    ac_int<EBITS-1, true> not_e = (a * b) + (c * d);
    return not_e;
}

int main()
{
    std::cout << "Testing a*b+c*d results for "<< EBITS << "bits and for "<<EBITS-1 <<"bits \n\n";
    bu a, b;
    bs c, d;
    ac_int<EBITS, true> e;
    ac_int<EBITS-1, true> not_e;
    ac_channel<bu> in_stream_ab;
    ac_channel<bs> in_stream_cd;

    std::srand(std::time(NULL));

    //filling the input ac_channels with test values
    for(int i=0; i<(2*SAMPLES); ++i) // double the samples since we use one channel 
    {                                // for two variables
        in_stream_ab.write(std::rand() % 21);
        in_stream_cd.write((std::rand() % 41) - 20);
    }

    //adding a test that will cause overflow in less bits
    in_stream_ab.write(255);
    in_stream_ab.write(255);
    in_stream_cd.write(-256);
    in_stream_cd.write(-256);
    
    while (in_stream_ab.available(2)) {
        a = in_stream_ab.read();
        b = in_stream_ab.read();
        c = in_stream_cd.read();
        d = in_stream_cd.read();
        e = calculate_e(a, b, c, d);
        not_e = calculate_not_e(a, b, c, d);

        std::cout << a << " * " << b << " + " << c << " * " << d << " = " << e << " OR " << not_e << std::endl;
    }

    std::cout << "There is an overflow when the two results don't match\n";
    std::cout << "Last test is supposed to cause overflow!!\n"; 
    return 0;

}
