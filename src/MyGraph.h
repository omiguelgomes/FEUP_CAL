#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "Graph.h"
#include "Estacao.h"
#include "Road.h"
#include "Camiao.h"
#include "Contentor.h"
#include "Parser.h"

using std::vector;

class MyGraph
{
private:
	//grafo original
	Graph<Node>* graph;

	//grafo after-processing
	Graph<Node>* finalGraph;

	//todas as ruas do grafo
	vector<Road*> roads;

	//matriz N^2 que indica se num dado cruzamento de roads h� um container
	vector<vector<bool>> containerPresent;

	//todos os camioes a circular no grafo
	vector<Camiao*> camioes;

	//todos os contentores no grafo
	vector<Contentor *> contentores;

	vector<Estacao *> estacoes;

public:
	MyGraph(string file_1, string file_2, string file_3);
	MyGraph & displayRoads();
	bool addTruck(Camiao * t);
	bool addContainer(Contentor * c);
	bool addStation(Estacao * s);
	vector<Vertex<Node>*> backPreProcess(vector<Vertex<Node>* > shortenedPath);
	void preProcess();
	void floydWarshallSP();
	void recalculateDistContainers(int currentVertexPos, bool isSort);
	vector<Vertex<Node>*> genOneTruck_NContainers(Camiao * c, Estacao * e);
	vector<vector<Vertex<Node>*>> genNTrucks_NContainers(Estacao * e, int N);

	//getters
	vector<Contentor *> getContentores();
	Graph<Node>* getGraph();
	Graph<Node>* getFinalGraph();
	vector<Camiao*> getCamioes();
	vector<Estacao*> getEstacoes();
	vector<int>  getContainderIDs();

	

	//setters
	void setContentores(vector<Contentor*> contentores);

};