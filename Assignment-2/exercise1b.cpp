//b) minimum bitwidth of specific operation

//ac_fixed<5,2,false> f;
//ac_fixed<5,4,true> g;
//ac_fixed<W,I,true> h=f*g; //How many bits

//assume
//4+2 = 6bits so the int part doesn't overflow.
//3+1 = 4bits so the frac part doesn't underflow.

#include <ac_fixed.h>
#include <ac_channel.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

static const int SAMPLES = 10;
static const int W = 10;
static const int I = 6;

typedef ac_fixed<5, 2, false> ftype;
typedef ac_fixed<5, 4, true> gtype;

void calculate_h(ftype f, gtype g,ac_fixed<W, I, true> &h,ac_fixed<W + 2, I + 1, true> &hmore,
                ac_fixed<W - 1, I, true> &h63, ac_fixed<W - 1, I - 1, true> &h54) {
    h = f * g;
    hmore = f * g;
    h63 = f * g;
    h54 = f * g;
}

int main()
{  
    //ac_fixed<5, 4, true>ff;
    //ff[0] = 1; ff[1] = 1; ff[2] = 1; ff[3] = 1; ff[4] = 0;
    //std::cout << ff.to_double();
    ftype f;
    gtype g;

    ac_fixed<W, I, true> h;
    ac_fixed<W+2, I+1, true> hmore;
    ac_fixed<W-1, I, true> h63;
    ac_fixed<W-1, I-1, true> h54;

    ac_channel<ftype> in_stream_f;
    ac_channel<gtype> in_stream_g;

    //creating a test that will cause overflow/underflow
    in_stream_f.write(0.125);
    in_stream_g.write(0.5);

    in_stream_f.write(3.825);
    in_stream_g.write(7.5);

    while (in_stream_f.available(1)) {
        f = in_stream_f.read();
        g = in_stream_g.read();

        calculate_h(f, g, h, hmore, h63, h54);

        std::cout << f << " * " << g << std::endl;
        std::cout << "10 bits = 6b int, 4b frac: " << h << std::endl;
        std::cout << "more than enough bits to show result = 7b int, 5b frac: " << hmore << std::endl;
        std::cout << "9 bits should cause overflow or underflow:\n";
        std::cout << "9 bits = 6b int, 3b frac: " << h63 << std::endl;
        std::cout << "9 bits = 5b int, 4b frac: " << h54 << std::endl << std::endl;
    }

    return 0;
}
