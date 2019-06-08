#pragma once

#include <string>
#include <vector>
#include "Node.h"
#include "Road.h"
#include "Graph.h"
#include "Estacao.h"
#include "Contentor.h"

using namespace std;


class Parser{
public:
    Parser();
    vector<Node *> getNodesLatLon(string fileName1);
    vector<Road *> getRoadEdges(string fileName2, vector<Node *> nodes);    
    vector<Estacao *> getEstacaoEdges(string fileName2, vector<int> tagEstacoes, vector<Node*> nodes);
    vector<Contentor *> getContentorEdges(string fileName2, vector<int> tagContentores, vector<Node*> nodes);
	Graph<Node> * getGraphFromFiles(string f1, string f2, string f3, vector<Road *> & roads, vector<Contentor *> & contentores, vector<Estacao *> estacoes);
};
