#ifndef PPM_H
#define PPM_H

#include "Converter.h"
#include "tools.h"

#include <bits/stdc++.h>
using namespace std;

typedef struct RGB
{
    unsigned int red,blue,green;
    RGB(): red(0),green(0),blue(0){}
}RGB;



class PPM : public Converter
{
    public :
        void convertAndOutput();
        ~PPM();
    private :
        int rgbTograyscale(RGB);
        int readppm();
        void writetopgm();
        int width=0;
        int height=0;
        int maxcolorval = 0;
        vector<RGB> pixels;    
};

#endif