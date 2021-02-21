//mean filter 1x5 

#include <iostream>
#include <ac_int.h>

static const int N=280; //N=row
static const int M=360; //M=column

//pixel values 0...255 => 8bits unsigned
//to compute mean we add 5 pixels
//out representation needs 8+5=13 bits 

typedef ac_int<13,false> pixeltype;

//#pragma hls_design top
void filter(pixeltype img[N][M], pixeltype out[N][M]) {
	static pixeltype zero=0;
ROW:for(int i=0; i<N; ++i) {
COL:	for(int j=0; j<M; ++j) {
			pixeltype p1 = (j > 1) ? img[i][j-2]: zero;
			pixeltype p2 = (j > 0) ? img[i][j-1]: zero;
			pixeltype p3 = img[i][j];
 			pixeltype p4 = (j < M-1) ? img[i][j]: zero;
			pixeltype p5 = (j < M-2) ? img[i][j+2]: zero;

			out[i][j] = (p1 + p2 + p3 + p4 + p5) / 5;
		}
	}
}

int main() {
	return 0;
}