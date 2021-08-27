#include"tools.h"
#include<vector>
#include<string>
#include<sstream>
using namespace std;

vector<string> split(string &tosplit, char delimiter) {

    vector<string> v;

    stringstream check(tosplit);
    string intermediate;

    while(getline(check, intermediate, delimiter)) 
    { 
        v.push_back(intermediate);
    }

    return v;
}

// This functions removes any extra space that is present, at the front
// or inbetween
string removeExtraSpaces(string &str) {

	string res = "";
	bool remover = 1;
	for(int i = 0; i < str.length(); i++) {

		if(str[i] == ' ' && remover) continue;

		if(str[i] == ' ' && !remover) {
			remover = 1;
			res.push_back(str[i]);
		}
		else if(str[i] != ' ') {
			remover = 0;
			res.push_back(str[i]);
		}
	}

	while(!res.empty() && res.back() == ' ') res.pop_back();

	return res;
}