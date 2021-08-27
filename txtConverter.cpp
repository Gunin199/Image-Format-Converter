#include<bits/stdc++.h>
using namespace std;
#include "txtConverter.h"


txtConverter :: ~txtConverter()
{
    
}

void txtConverter :: convertAndOutput()
//int main()
{
    string line, str;

    char ch;

    int lines = 0, words = 0, size, ch_spaces = 0, ch_nospaces = 0, spaces= 0;

    ifstream file = loadFile();             //Declares the variable file which can only be readed

    //ifstream file;

    //file.open("input.txt");

    file.seekg(0, ios::end);                //this will set position of the next character to the end of the buffer

    size = file.tellg();                    //gives the current get position of the pointer 

    file.seekg(0,ios::beg);                 //this will set the position to the start of the buffer

    while(getline(file, line))              //reads the input line from the stream
    {
        ch_spaces += line.size();           //gets the total no. of characters with spaces

        lines++;                            //gets increased every time while loop runs because it checks each individual line

        for(int i=0; i<line.size(); i++)    //for loop to find total no. of spaces
        {
            if(isspace(line[i]))            //checks if there is a space in line 
            {
                spaces++;
            }
        }
    }

    file.clear();

    file.seekg(0, ios::beg);                //Again sets the position to the beginning

    ch_nospaces = ch_spaces - spaces;       //remove spaces from ch_spaces to get characters without spaces

    ch_spaces = ch_spaces + lines -1;       //we need to add total no.of lines to the character with spaces to include \n too 
        
    ofstream file2;                         //declares the variable file2 which can be writed

    file2.open("output.txt");
    
    while(file>>str)                        //loop to find string(or)words in the line 
    {
        words++;
    }

    file2<<"DOCUMENT STATISTICS\n\n";       //this line helps to write in file2

    file2<<"Lines : "<<lines<<"\n";

    file2<<"Words : "<<words<<"\n";

    file2<<"Characters(with spaces) : "<<ch_spaces<<"\n";

    file2<<"Characters(no spaces) : "<<ch_nospaces<<"\n";

    file2<<"Bytes : "<<size -1<<"\n\n";

    file.clear();

    file.seekg(0,ios::beg);                 //sets the pointer to start of input stream

    if(file && file2)
    {
        while(getline(file, line))          //loop to print each line in output file
        {
            file2 <<line<< "\n";
        }
    }

    //file.close();

    file2.close();                          //closes the file
    
    //return 0;
}