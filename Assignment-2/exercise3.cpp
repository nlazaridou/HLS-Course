#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ac_int.h>
#include <ac_channel.h>

static const int TESTS=10;

typedef ac_int<4,false> dtype;

class RunLengthEncoder{
	private:
		dtype num;
		dtype nextNum;
		dtype count;
	public:
		RunLengthEncoder(){
			num=0;
			nextNum=0;
			count=0;
		}

		void run(ac_channel<dtype> &in, ac_channel<dtype> &out) {
			if (in.available(10)) {
				num=in.read();
				count=1;
				for(int i=0; i<9; ++i) {
					nextNum=in.read();
					if(num==nextNum) {
						count++;
					}
					else {
						out.write(num);
						out.write(count);
						num = nextNum;
						count = 1;
					}
				}

				out.write(num);
				out.write(count);
			}
		}
};

int main(){
	std::srand(std::time(NULL));

	for (int i=0; i<TESTS;i++) {

		ac_channel<dtype> in_test;
		ac_channel<dtype> out_test;

		std::cout<<"\n\nTest "<< i+1 << " In Vector: ";

		for (int j=0; j<10; ++j) {
			int in = std::rand()%16;
			in_test.write(in);
			std::cout<<in<<" ";
		}

		RunLengthEncoder encoder;
		encoder.run(in_test, out_test);

		std::cout<<"\nOut vector: ";

		while (out_test.available(1)) {
			dtype out = out_test.read();
			std::cout<<out<<" ";
		}
	}

	return 0;
}
