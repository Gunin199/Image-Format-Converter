#include <vector>
#include <string>
using namespace std;
#include "gdfConverter.h"
#include "tools.h"


void gdfConverter::convertAndOutput() {

	// This contains the different nodes availaible with us
	vector<string> nodeNames; 
	// This contains the graph without edge weights
	map<string, unordered_set<string>> graph;


	// This map contains mapping from edge to edge weights
	map<pair<string,string>, double> edgeWeight;
	// This map contains mapping to labels
	unordered_map<string, string> labels;


	// Read the file
	ifstream file = loadFile();
	string str;

	int readingNodes = 0;
	int readingEdges = 0;

	vector<pair<string,string>> nodeformat;
	vector<pair<string,string>> edgeformat;

	// Maps the column number to attribute
	unordered_map<int, string> nodeAttrib;
	unordered_map<int, string> edgeAttrib;



	// READ THE FILE LINE BY LINE
	while (getline(file, str)) {


		// Getting the line by line input from file
		vector<string> line = split(str, ',');
		for(int i = 0; i < line.size(); i++) {
			line[i] = removeExtraSpaces(line[i]);
		}


		// If the line is defining the node format, store the nodeFormat
		if(readingNodes == 0 && line[0].length() >= 8 && line[0].substr(0,8) == "nodedef>") {
			line[0] = line[0].substr(8, line[0].length() - 8);
			line[0] = removeExtraSpaces(line[0]);
			readingNodes = 1;

			int columnNo = 0;
			for(string s : line) {
				vector<string> v = split(s, ' ');

				nodeAttrib[columnNo] = v[0];
				columnNo++;

				// This pair stores the attribute and the type of attribute
				pair<string, string> pp{v[0], v[1]};
				nodeformat.push_back(pp);
			}

			continue;
		}


		// If the line is defining the edge format, store the edgeFormat
		if(readingEdges == 0 && line[0].length() >= 8 && line[0].substr(0,8) == "edgedef>") {
			line[0] = line[0].substr(8, line[0].length() - 8);
			line[0] = removeExtraSpaces(line[0]);
			readingEdges = 1;
			readingNodes = 2;

			int columnNo = 0;
			for(string s : line) {
				vector<string> v = split(s, ' ');

				edgeAttrib[columnNo] = v[0];
				columnNo++;

				// This pair stores the attribute and the type of attribute
				pair<string, string> pp{v[0], v[1]};
				edgeformat.push_back(pp);
			}

			continue;
		}


		// IF THE LINE IS READING A NODE, READ IT ACCORDING TO FORMAT
		if(readingNodes == 1) {

			string name, label;
			for(int j = 0; j < line.size(); j++) 
			{
				if(nodeAttrib[j] == "name") {
					name = line[j];
				}
				if(nodeAttrib[j] == "label") {
					label = line[j];
				}
			}
			nodeNames.push_back(name);
			labels[name] = label;
		}


		// IF THE LINE IS READING AN EDGE, READ IT ACCORDING TO FORMAT
		if(readingEdges == 1) {

			bool isDirected = 0;
			for(int j = 0; j < line.size(); j++) 
			{
				if(edgeAttrib[j] == "directed") {

					if(line[j] == "true") isDirected = 1;
					break;
				}
			}

			string node1, node2;
			double weight; 
			for(int j = 0; j < line.size(); j++) 
			{
				if(edgeAttrib[j] == "node1") node1 = line[j];
				else if(edgeAttrib[j] == "node2") node2 = line[j];
				else if(edgeAttrib[j] == "weight") weight = stof(line[j]);
			}

			if(isDirected) {

				edgeWeight[pair<string,string>(node1, node2)] = weight;
				graph[node1].insert(node2);
			}
			else {
				edgeWeight[pair<string,string>(node1, node2)] = weight;
				graph[node1].insert(node2);

				edgeWeight[pair<string,string>(node2, node1)] = weight;
				graph[node2].insert(node1);
			}

		}
	}


	
	// Creating a csv file and writing the graph into it
	ofstream outputfile;
	string oname = split(currentFile, '.')[0] + "_out.csv";
	outputfile.open(oname.c_str());

	outputfile << "";
	for(string &x : nodeNames) {
		outputfile << "," << x;
	}
	outputfile << endl;



	for(string &x : nodeNames) {

		outputfile << x;
		for(string &y : nodeNames) {

			if(x == y) {
				outputfile << "," << 0;
				continue;
			}

			if(graph[x].count(y)) {
				outputfile << "," << edgeWeight[pair<string,string>(x,y)];
			}
			else {
				outputfile << "," << "-n/a-";
			}
		}
		
		outputfile << endl;
	}
	
}


gdfConverter::~gdfConverter() {
	
}


