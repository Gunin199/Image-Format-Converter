#ifndef CONVERTER_H
#define CONVERTER_H

#include <bits/stdc++.h>
#include "ErrorHandler.h"

using namespace std;


class Converter {
protected:
	string currentFile;
	
public:
	ifstream loadFile();
	void setFile(string);
	virtual void convertAndOutput() = 0;
	virtual ~Converter();
};

#endif 