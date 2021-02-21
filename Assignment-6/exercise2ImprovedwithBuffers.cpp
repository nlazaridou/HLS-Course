//mean filter 1x5 

#include <iostream>
#include <ac_int.h>

static const int N=280; //N=row
static const int M=360; //M=column

//pixel values 0...255 => 8bits unsigned
//to compute mean we add 5 pixels => out needs 8+5=13 bits 

typedef ac_int<13,false> pixeltype;

//#pragma hls_design top
void filter(pixeltype img[N][M], pixeltype out[N][M]) {
	static pixeltype zero=0;
ROW:for(int i=0; i<N; ++i) {
		pixeltype pixelCache[4]; //pixel buffer
		pixelCache[0]=0;
		pixelCache[0]=0;
		pixelCache[0]=img[N][0];
		pixelCache[0]=img[i][1];
COL:	for(int j=0; j<M; ++j) {
			pixeltype newPixel = (j < M-2) ? img[i][j+2]: zero;
			//out[i][j] = (p1 + p2 + p3 + p4 + p5) / 5;
			out[i][j] = (pixelCache[0] + pixelCache[1] + pixelCache[2] + pixelCache[3] + newPixel) / 5;
			
			//shifting the data in the buffer
			pixelCache[0]=pixelCache[1];
			pixelCache[1]=pixelCache[2];
			pixelCache[2]=pixelCache[3];
			pixelCache[3]=newPixel;
		}
	}
}

int main() {
	return 0;
}