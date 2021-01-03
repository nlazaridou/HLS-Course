#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ac_int.h>
#include <ac_channel.h>

static const int TESTS=10;

typedef ac_int<4,false> dtype;
typedef ac_int<1,false> booltype;

class RunLengthEncoder{
	private: //internal state
		dtype current;
		dtype previous;
		dtype count;
		booltype firstTime;
	public: //constructor - init internal state
		RunLengthEncoder(){
			current=0;
			previous=0;
			count=1;
			firstTime=1;
		}
		//top-level interface
		void run(ac_channel<dtype> &in, ac_channel<dtype> &out) {
			if (in.available(1)) {
				current=in.read();
				if(firstTime==1) {
					previous=current;
					firstTime=0;
				}
				else if(current==previous) {
					count++;
				}
				else {
					out.write(previous);
					out.write(count);
					previous = current;
					count = 1;
				}
			}
			else {
				//if we have empty stream we dont want to produce an output
				if(firstTime==0) {
					out.write(current);
					out.write(count);
				}

			}
		}
};

int main(){
	std::srand(std::time(NULL));

	for (int i=0; i<TESTS;i++) {
		int streamLength=std::rand()%15;
		ac_channel<dtype> in_test;
		ac_channel<dtype> out_test;

		std::cout<<"\n\nTest "<< i+1 << " In Vector: ";

		for (int j=0; j<streamLength; ++j) {
			int in = std::rand()%16;
			in_test.write(in);
			std::cout<<in<<" ";
		}

		RunLengthEncoder encoder;
		for (int j=0; j<streamLength+1; ++j) {
			encoder.run(in_test, out_test);
		}
		
		std::cout<<"\nOut vector: ";

		while (out_test.available(1)) {
			dtype out = out_test.read();
			std::cout<<out<<" ";
		}
	}

	return 0;
}
