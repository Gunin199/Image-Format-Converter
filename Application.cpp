#include <bits/stdc++.h>
#include "Application.h"
#include "Converter.h"
#include "gdfConverter.h"
#include "tools.h"
#include "ppmConverter.h"
#include "txtConverter.h"
#include "csvConverter.h"
using namespace std;

Application::Application(string fileName)
{
	currentFile = fileName;
}

void Application::read(int choice)
{
	Converter *c = NULL;

	string extension = split(currentFile,'.').back();
	try{
		switch (choice)
		{
		case 1:
			if(extension.compare("gdf")==0)	
			{
				c = new gdfConverter();
			}
			else
			{
				throw FileException("Not a GDF File");
			}
			break;
		case 2:
			if(extension.compare("ppm")==0)
			{
				c = new PPM();
			}
			else
			{
				throw FileException("Not a PPM File");
			}
			break;
		case 3:
			if(extension.compare("txt")==0)
			{
				c= new txtConverter();
			} 
			else
			{
				throw FileException("Not a Txt File");
			}
			break;
		case 4:
			if(extension.compare("csv")==0)
			{
				c = new csvConverter();	
			}
			else
			{
				throw FileException("Not a Csv File");
			}
			break;
		default:
			break;
		}
		c->setFile(currentFile);
		c->convertAndOutput();
	}
	catch (FileException& e) //exception in choice made or while creating ifstream object
	{
		cout << '\n' << e.what() << "\n\n";
	}
	catch (...) //any other exception that occurs
	{
		cout << "\nError while processing :(" << "\n\n";
	}
	delete c;
}

void Application ::print_menu()
{
	cout << "MENU :\n";
	cout << "1. GDF to CSV converter\n";
	cout << "2. PPM to PGM converter\n";
	cout << "3. Text File Reader\n";
	cout << "4. CSV File Reader\n";
	cout << "5. Exit\n";
	cout << "Choose an option from above: ";
}

void Application ::putFile(string s)
{
	currentFile = s;
}