#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include<algorithm>
#include "csvConverter.h"
#include "tools.h"
#include<cctype>
using namespace std;

csvConverter::~csvConverter() {

}

void csvConverter::convertAndOutput()
{
    vector<vector<string>> vec;        //2d vector of strings.
    string txt,line; 
    ifstream Myfile = loadFile();;  //giving the name of the file to read
    int rows=0,columns = 0;
    while(getline(Myfile,txt))           
    {
        vector<string> temp;     
        vec.push_back(temp);         //pushing an empty vector array to this 2-d vector array
        columns = 0;
        stringstream string1(txt); 
        while(getline(string1, line,','))   //reading all the values between ',' separation.
        { 
            vec[rows].push_back(line);   //pushing those values to the 2-d vector array
            columns++;
        } 
        rows++;    //incrementing the rows
    }
  
  int m = vec.size();
  int n = vec[0].size();
    vector<string> temp1; 
  if(isdigit(vec[0][0][0])){   //checking whether the  row,first column starts with integer or string
    for(int i=0;i<vec.size()-1;i++)
    {
      for(int j=0;j<vec.size()-1-i;j++)
      {
        if(stof(vec[j][0])>stof(vec[j+1][0]))  //comparing the float values of 2rows of the first coloumn
	{
	  temp1=vec[j];   //swapping
	  vec[j]=vec[j+1];
	  vec[j+1]=temp1;
	  //break;
	}
	if(stof(vec[j][0])==stof(vec[j+1][0]))          //if the 2 values are equal
	{
	 if((int)vec[0][1][0]>=48 && (int)vec[0][1][0]<=57){  //string1ing whether the second coloumn is an int
	   if(stof(vec[j][1])>stof(vec[j+1][1]))  //if the second column is an int,then compare the float values
           {
             temp1=vec[j];    //swapping
             vec[j]=vec[j+1];
             vec[j+1]=temp1;
	    // break;
           }
	  }
	else    //if it is not int
	{
	  if(vec[j][1]>vec[j+1][1]) //string comparison
	  {
	    temp1=vec[j];
             vec[j]=vec[j+1];
             vec[j+1]=temp1;
	  }
	}
       }
      }
    }
 }
 else    //if first row starts with some string
 {
   for(int i=0;i<vec.size()-1;i++)
    {
      for(int j=0;j<vec.size()-1-i;j++)
      {
        if((vec[j][0])>(vec[j+1][0]))  //comparing strings
        {
          temp1=vec[j];   //swapping takes place
          vec[j]=vec[j+1];
          vec[j+1]=temp1;
          //break;
        }
        if((vec[j][0])==(vec[j+1][0]))    //if 2 values are equal
        {
	  if((int)vec[0][0][0]>=48 && (int)vec[0][0][0]<=57){   //checking whether the second coloumn starts with int
           if(stof(vec[j][1])>stof(vec[j+1][1]))  //if it is some number,then comparing float values
           {
             temp1=vec[j];  //swapping 
             vec[j]=vec[j+1];
             vec[j+1]=temp1;
            // break;
           }
        }
	else   //if it is not int
        {
          if((vec[j][1])>(vec[j+1][1]))
          {
            temp1=vec[j];
             vec[j]=vec[j+1];
             vec[j+1]=temp1;
          }
        }
      }
    }
 }
}

   ofstream myfile("test4.csv");  //writing to a new file test2.csv
   for(int i=0;i<vec.size();i++)
   {
     for(int j=0;j<vec[i].size();j++)
     {
       myfile<<vec[i][j]<<",";  //writing to test2.csv 
     }
     myfile<<endl;
   }

   myfile.close();//closing the file
 
}
