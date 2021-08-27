#include<bits/stdc++.h>
using namespace std;
#include "Application.h"



int main() 
{
	int choice;
	string name;
	while(1)
	{
		Application :: print_menu();
		 
		try
		{
			cin >> choice;
			if(cin.fail())
			{
				cin.clear();
				cin.ignore(32767,'\n');
				cout << "\nPlease enter an integer\n\n";
				continue;
			}
			else
			{
				cin.ignore(32767,'\n');
			}			

			if(!(choice==1 || choice==2 || choice==3 || choice==4 || choice==5))
			{
				throw "Invalid choice made";
			}
		}
		catch(const char* e)
		{
			cout << '\n' << e << "\n\n";
			continue; 
		}

		//exit the program
		if(choice==5)
		{
			return 0;
		}
		
		cout << "Enter input file name : ";
		cin >> name;	//input the name of input file
		cin.ignore(32767,'\n');
		
		Application * app = new Application(name);

		//perform respective task according to choice
		app->read(choice);
	}

	return 0;
}
