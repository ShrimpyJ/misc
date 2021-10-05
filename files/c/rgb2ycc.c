#include <stdio.h>
#include <stdlib.h>

unsigned char RGB_to_Y(unsigned char R, unsigned char G, unsigned char B)
{
	return 16
	          + (
	              ((R<<6) + (R<<1)
	             + (G<<7) + G
	             + (B<<4) + (B<<3) + B)
	          >>8);
}

unsigned char RGB_to_Cb(unsigned char R, unsigned char G, unsigned char B)
{
	return 128
	           + (
	               ~(R<<5) + (R<<2) + (R<<1)
	             + (~((G<<6) + (G<<3) + (G<<1)))
	             + (B<<7) + (~(B<<4))
	           >>8);
}

unsigned char RGB_to_Cr(unsigned char R, unsigned char G, unsigned char B)
{
	return 128
	           + (
	               ~(R<<4) + (R<<7)
               + ~((G<<6) + (G<<5) + ~(G<<1))
	             + ~((B<<4) + (B<<1))
	           >>8);
}

int main(int argc, char** argv)
{
	unsigned char R, G, B;
	unsigned char Y, Cb, Cr;
	
	if (argc != 4){
		fprintf(stderr, "usage: rgb2ycc R G B\n");
		exit(1);
	}

	R = atoi(argv[1]);
	G = atoi(argv[2]);
	B = atoi(argv[3]);

	Y = RGB_to_Y(R, G, B);
	Cb = RGB_to_Cb(R, G, B);
	Cr = RGB_to_Cr(R, G, B);

	printf("(%d, %d, %d)\n", Y, Cb, Cr);
}
