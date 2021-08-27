#include<string>
#include"Converter.h"

ifstream Converter::loadFile() {
	ifstream ifp(currentFile.c_str());
	if(ifp.fail())
	{
		throw FileException("File not found");
	}
	return ifp;
}

void Converter::setFile(string filename)
{
	currentFile = filename;
}

Converter :: ~Converter(){}
