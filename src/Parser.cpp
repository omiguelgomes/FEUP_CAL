#include "Graph.h"
#include "Parser.h"
#include "Node.h"
#include "Road.h"
#include "Contentor.h"
#include "Estacao.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

Parser::Parser()
{}

vector<Node *> Parser::getNodesLatLon(string fileName1)
{
   
    ifstream readFile(fileName1);

    if(!readFile.is_open())
    {
        cerr << "No file found" << endl;
		return vector<Node*>();
    }

    string line;
    vector<string> lines;
    vector<Node *> nodes;
    vector<string> nodeInfo;
    
    Node * node;

	while(getline(readFile, line))
    {
		int stringSize = line.length();
		line = line.substr(1, stringSize - 2);
        lines.push_back(line);
	}

    for(unsigned int i = 1; i <  lines.size(); i++)
    {
        
		string delimiter = ",";
        string s = lines[i];

		string val;
		string vals[3];
		int j = 0;
		while(j < 3)
		{
			val = s.substr(0, s.find_first_of(delimiter));
			vals[j] = val;
			s.erase(0, s.find(delimiter) + 2);
			j++;
		}
        
        node = new Node (atoi(vals[0].c_str()), stod(vals[1]), stod(vals[2]));
		


        nodes.push_back(node);
    }


	cout << " Completo" << endl;
    return nodes;
}

//------------------------------------- Helper func---
Node* findNode(vector<Node*> nos, int id)
{
	for (auto no : nos)
	{
		if (no->getID() == id)
		{
			return no;
			break;
		}
	}

	return nullptr;
}

vector<Estacao *> Parser::getEstacaoEdges(string fileName2, vector<int> tagEstacao, vector<Node*> nodes)
{
	ifstream readFile(fileName2);
	string line;
    vector<Estacao *> estacoes;
	
	vector<string> lines;
	int stringSize = 0;

	if (!readFile.is_open())
	{
		cerr << "No file found" << endl;
		return vector<Estacao *>();
	}
    
    while(getline(readFile, line))
    {
		int stringSize = line.length();
		line = line.substr(1, stringSize - 2);
        lines.push_back(line);
    }

	for (int i = 1; i < lines.size(); i++) {
		for (int j = 0; j < tagEstacao.size(); j++) {
			string delimiter = ",";
			string s = lines[i];
			stringSize = s.length();
			s = s.substr(1, stringSize - 2);
			string val;
			string vals[3];
			int v = 0;
			while(v < 3)
			{
				val = s.substr(0, s.find_first_of(delimiter));
				vals[v] = val;
				s.erase(0, s.find(delimiter) + 2);
				v++;
			}
			if (tagEstacao.at(j) == lines.at(i).at(0)) {

				 estacoes.push_back(new Estacao (stoi(vals[0]), stod(vals[1]), stod(vals[2])));
			}
		}
	}

	return estacoes;
}

vector<Contentor *> Parser::getContentorEdges(string fileName2, vector<int> tagContentor, vector<Node*> nodes)
{
	ifstream readFile(fileName2);
	string line;
    vector<Contentor *> contentores;
	
	vector<string> lines;
	int stringSize = 0;

	if (!readFile.is_open())
	{
		cerr << "No file found" << endl;
		return vector<Contentor *>();
	}
    
    while(getline(readFile, line))
    {
		int stringSize = line.length();
		line = line.substr(1, stringSize - 2);
        lines.push_back(line);
    }

	for (int i = 1; i < lines.size(); i++) 
	{
		for (int j = 0; j < tagContentor.size(); j++) 
		{
			string delimiter = ",";
			string s = lines[i];
			string val;
			string vals[3];
			int v = 0;
			while(v < 3)
			{
				val = s.substr(0, s.find_first_of(delimiter));
				vals[v] = val;
				s.erase(0, s.find(delimiter) + 2);
				v++;
			}
			if (tagContentor.at(j) == lines.at(i).at(0)) {

				 contentores.push_back(new Contentor (stoi(vals[0]), stod(vals[1]), stod(vals[2])));
			}
		}
	}

	return contentores;
}

vector<Road *> Parser::getRoadEdges(string fileName2, vector<Node *> nodes)
{
    ifstream readFile(fileName2);
	string line;
    vector<Road *> roads;
	vector<string> lines;


	if (!readFile.is_open())
	{
		cerr << "No file found" << endl;
		return vector<Road *>();
	}
    
    while(getline(readFile, line))
    {
		int stringSize = line.length();
		line = line.substr(1, stringSize - 2);
        lines.push_back(line);
    }

	vector <pair<int, int>> edges;
	for (unsigned int i = 1; i < lines.size(); i++)
	{
		int id = 0;
		string delimiter = ",";
		string s = lines[i];

		string val;
		string vals[2];
		int j = 0;

		while (j < 2)
		{
			val = s.substr(0, s.find_first_of(delimiter));
			vals[j] = val;
			s.erase(0, s.find(delimiter) + 2);
			j++;
		}
		edges.push_back(make_pair(stoi(vals[0]), stoi(vals[1])));
	}

	for (int i = 0; i < edges.size(); i++)
	{
		roads.push_back(new Road(i + 1, findNode(nodes, edges[i].first), findNode(nodes, edges[i].second)));
	}
    
	return roads;
}

Graph<Node> * Parser::getGraphFromFiles(string f1, string f2, string f3, vector<Road *> & roads, vector<Contentor *> & contentores, vector<Estacao *> estacoes)
{
	vector<Node*> nodes;
	Graph<Node>* grafo = new Graph<Node>;
    

    ifstream readTag(f3);
	string tag;

    vector<int> tagContentores;
    int countContentores = 0;

    vector<int> tagEstacoes;
    int countEstacoes = 0;

	int countLines = 0;

    while(getline(readTag, tag))
    {
		
        if (tag == "contentores") {
            getline(readTag, tag);
            countContentores = stoi(tag);
            while(countContentores > 0) {
                getline(readTag, tag);
                tagContentores.push_back(stoi(tag));
                countContentores--;
            }
        }

        if (tag == "estacoes") {
            getline(readTag, tag);
            countEstacoes = stoi(tag);
            while(countEstacoes > 0) {
                getline(readTag, tag);
                tagEstacoes.push_back(stoi(tag));
                countEstacoes--;
            }
        }
	}

	//nodes
	cout << "Transmitindo informacao dos nodes para o grafo...";
	nodes = getNodesLatLon(f1);
	for (auto no : nodes)
		grafo->addVertex(*no);
	cout << "... Completo: (" << grafo->getNumVertex() << " Nos)." << endl;

	//ruas
	cout << "Transmitindo informacao das ruas...";
	roads = getRoadEdges(f2, nodes);
	cout << "... Completo: (" << roads.size() << " ruas)." << endl;

	//contentores
	cout << "Transmitindo informacao dos contentores...";
	contentores = getContentorEdges(f2, tagContentores, nodes);
	cout <<"... Completo: (" << tagContentores.size() << " contentores)." << endl;

	//estacoes
	cout << "Transmitindo informacao das estacoes...";
	estacoes = getEstacaoEdges(f2, tagEstacoes, nodes);
	cout << "... Completo: (" << tagEstacoes.size() << " estacoes)." << endl;

	return grafo;
}