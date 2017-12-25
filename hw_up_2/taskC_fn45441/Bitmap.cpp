
#include "Bitmap.h"

#include <iostream>

//TODO
bool color_check(unsigned int color, int pix_color, double pr );

void find_ends(unsigned int *image, int h, int w, unsigned int *poins, unsigned int color = 0xFFFFFFFF);

void rewrite_image(unsigned int *image, int width, int height, unsigned int* new_size );

double grey(unsigned int color);


int main()
{
	const size_t MAX_SIZE = 100000;

	unsigned int width, height, image[MAX_SIZE], color;

    std::cin>>color;

	int rval;
	rval = LoadBitmap("test.bmp", image, MAX_SIZE, width, height);

	if (rval != ALL_OK)
	{
		std::cerr << "Cannot load image data from test.bmp! Error code " << rval << "\n";
		return 1;
	}

    unsigned int end_dots[4]; // горна дясна долна лява
    find_ends(image, height, width, end_dots,color);


    rewrite_image(image, width, height,end_dots);
	width = end_dots[1] - end_dots[3] + 1;
	height = end_dots[2] - end_dots[0] + 1;


    rval = SaveBitmap("test_new.bmp", image, width, height);

	if (rval != ALL_OK)
	{
		std::cerr << "Cannot save image data to test_new.bmp! Error code " << rval << "\n";
		return 2;
	}

    return 0;
}

void find_ends(unsigned int *image, int h, int w, unsigned int *poins, unsigned int color){

    int max_size = ( h>w )? h : w;

    unsigned int &left = poins[3], &rigth = poins[1];
    left = w-1;
    rigth = 0;

    unsigned int &top = poins[0], &bottom = poins[2];
    top = h-1;
    bottom = 0;

    for ( int i = 0; i<max_size ; i++){
        for ( int j=0; j<max_size ; j++){

            // обхожда по редове
            if (( j<w )&&( i<h )){
                if(image[i*w+j] != color && j<left)
                    left = j;
                if (image[(i+1)*w - j - 1] != color && w-1-j > rigth)
                    rigth = w-1-j;
            }

            // обхожда по колони
            if ( j<h && i<w ){

                if(image[j*w + i] != color && j<top)
                    top = j;

                int index = (h-1-j)*w + i;
                if (image[index] != color && h-1-j> bottom)
                    bottom = h-1-j;
            }
        }
    }
}

bool color_check(unsigned int color, int pix_color, double pr){
    bool result;

    double color_g = grey(color);
    double pix_color_g = grey(pix_color);

    double color_pr = (pix_color_g / color_g) * 100;

    double d = 100 - pr;

    result = color_pr > 100.-d && color_pr<100.+d;

    return result;


}

void rewrite_image(unsigned int *image, int width, int height, unsigned int* new_size ){
     int counter = 0;
     for (int i = new_size[0]; i<new_size[2]+1 ; i++){
        for (int j=new_size[3]; j<=new_size[1]; j++){
            image[counter] = image[i*width + j];
            counter ++;
        }
    }
}

double grey(unsigned int color){
    int color_r = (color>>16)&0xFF;
    int color_g = (color>>0x8)&0xFF;
    int color_b = color&0xFF;

    double color_gc = (color_b+color_g+color_r)/3.;

    return color_gc;
}
