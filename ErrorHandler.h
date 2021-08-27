#ifndef ERR_H
#define ERR_H

#include<string>
#include<exception>

using namespace std;

class FileException : public exception
{

public:
	string message;
	FileException(string = "Invalid Filename");

	const char * what () const throw ();
};

#endif