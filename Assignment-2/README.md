## 2nd Programming Assignment


### Exercise 1
a) For the given example choose the minimum number of bits necessary to accurately represent the result.

    ac_int<8,false> a, b; // 8−bit unsigned integer
    ac_int<9,true> c, d; // 9−bit signed integer
    ac_int<?,true> e = a∗b + c∗d; // How many bits

b) For the given example choose the minimum number of bits necessary to accurately represent the result.

    ac_fixed<5,2,false> f; //5−bit unsigned fixed−point type with 2 integer bits 
    ac_fixed<5,4,true> g; // 5−bit signed fixed−point type with 4 integer bits
    ac_fixed<?,?,true> h = f∗g; // How many bits
 
Create adequate test examples to check the result for the number of bits you chose.

### Exercise 2

Write two functions in C++. The first function takes as input a signed int of W bits <code>(ac_int<W,true>)</code> and calculates its canonic signed digit (CSD) representation. The second function takes the CSD representation of a constant and a signed int and calculates their product  with shifts and additions/subtractions.

The CSD representation represents signed int numbers with the digits -1, 0, 1 ensuring minimum non-zero digits. For example the number 011101 = 29 can be represented as 100<ins>1</ins>01=32-4+1 reducing the non-zero digits from 4 to 3 (-1 is represented by  <ins>1</ins>). You can read more at:

[https://www.allaboutcircuits.com/technical-articles/an-introduction-to-canonical-signed-digit-representation/](https://www.allaboutcircuits.com/technical-articles/an-introduction-to-canonical-signed-digit-representation/)

Each CSD number is stored in two bit strings: x+ and x-. The x+ number is a bit string of only the positive 1s of the representation and the x- is a bit string of the negative 1s. For example the number 100<ins>1</ins>01 that follows the CSD representation is saved as x+ = 100001 and x-=000100. The value of the number is always equal to [x+] - [x-]. According to this your function could have the following definition:

    template <int W>
    void csd_encode(ac_int<W, true>& num, ac_int<W, false>& x_p, ac_int<W, false> & x_m) {
    // num is the input number to be encoded in CSD
    // x_p and x_m are the two bit vectors that represent the CSD number
    }
Alternatively you can define a struct for the CSD numbers and use it as your function's arguments

    template <int W> 
    struct CSD {
    ac_int<W,false> x_p;
    ac_int<W,false> x_n;
    };
    …
    template <int W>
    void csd_encode (ac_int<W, true> &num, CSD<W> &num_csd)
    
Since you can now calculate the CSD representation of a number or a constant you can implement "non-costly" multiplication operations between an integer and a constant using consecutive shifts and additions/subtractions. For example the operation 231* X could be calculated as:
(2<sup>7</sup> + 2<sup>6</sup> + 2<sup>5</sup> + 2<sup>2</sup> + 2<sup>1</sup> + 2<sup>0</sup>)*X

<img src="https://github.com/nlazaridou/hls-course/blob/main/Assignment-2/readme_img1.png">

or even better, calculated with fewer operations as: 
(2<sup>8</sup> - 2<sup>5</sup> + 2<sup>3</sup> - 2<sup>0</sup>)*X 

<img src="https://github.com/nlazaridou/hls-course/blob/main/Assignment-2/readme_img2.png">

because of the CSD represation 100<ins>1</ins>0100<ins>1</ins> of the constant 231.

The function of this multiplication could be defined as follows:

    ac_int<Wout,true> csd_mult (ac_int<W, true> &in, const CSD<W> &constant_csd) {
        // in is the input value (non constant)
        // x_p and x_m is the CSD representation of a constant
    }
For shifts and addition/subtraction you have to use operators from the ac_int class. Do not forget to create test cases with pseudo-random inputs for your functions.

### Exercise 3
We want to design a run length encoding circuit. The circuit takes as input 4-bit unsigned integers through an <code>ac_channel (ac_channel<ac_int<4,false> > &in)</code>. After ensuring that the channel has at least 10 values stored, you have to encode them so that consecutive elements of the same value are stored as a single data value and count.
For example this 10-element sequence 2 2 2 2 3 12 12 1 1 5 can be saved as **2** 4 **3** 1 **12** 2 **1** 2 **5** 1
(four 2s, one 3, two 12s etc...). The resulting consecutive pairs (value, count) should appear serially in an output channel ac_channel<ac_int<4,false> > &out after every input stream is processed. Create adequate test examples to check the result.

    void runlength_encode(ac_channel<ac_int > &in, 
    ac_channel<ac_int > &out)
