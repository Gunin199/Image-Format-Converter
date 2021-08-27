#ifndef TXTCONVERTER_H
#define TXTCONVERTER_H
#include "Converter.h"

using namespace std;

class txtConverter : public Converter
{
public:
	void convertAndOutput();
	~txtConverter();
};

#endif