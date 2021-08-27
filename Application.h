#ifndef APP_H
#define APP_H

#include <string>
#include "ErrorHandler.h"

using namespace std;

class Application {
private:
	string currentFile;
public:
	Application(string fileName);
	void putFile(string fileName);
	void read(int);
	static void print_menu();
};

#endif 