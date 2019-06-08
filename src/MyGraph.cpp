#include <iostream>

#include "MyGraph.h"

using namespace std;

MyGraph::MyGraph(string f1, string f2, string f3) 
{
	Parser parser;
	graph = parser.getGraphFromFiles(f1, f2, f3, roads, contentores, estacoes);
}

MyGraph & MyGraph::displayRoads()
{
	cout << roads.size() << "roads present:" << endl;

	for (unsigned int i = 0; i < roads.size(); i++)
	{
		Road road = *roads.at(i);

		cout << road << endl;
	}

	return *this;
}

vector<Contentor *> MyGraph::getContentores()
{
	return contentores;
}

Graph<Node>* MyGraph::getGraph()
{
	return graph;
}

Graph<Node>* MyGraph::getFinalGraph()
{
	return finalGraph;
}

vector<Camiao*> MyGraph::getCamioes()
{
	return camioes;
}

vector<Estacao*> MyGraph::getEstacoes()
{
	return estacoes;
}

void MyGraph::setContentores(vector<Contentor*> contentores)
{
	this->contentores = contentores;
}

bool MyGraph::addTruck(Camiao * t) 
{
	if (find(camioes.begin(), camioes.end(), t) == camioes.end()) 
	{
		camioes.push_back(t);
		return true;
	}
	return false;
}

bool MyGraph::addContainer(Contentor * c) {
	if (find(contentores.begin(), contentores.end(), c) == contentores.end()) {
		contentores.push_back(c);
		return true;
	}
	return false;
}

bool MyGraph::addStation(Estacao * s) {
	if (find(estacoes.begin(), estacoes.end(), s) == estacoes.end()) {
		estacoes.push_back(s);
		return true;
	}
	return false;
}

vector<int> MyGraph::getContainderIDs() {
	vector<int> res;
	for (auto c : contentores)
		res.push_back(c->getID());
	return res;
}

vector<Vertex<Node>*> MyGraph::backPreProcess(vector<Vertex<Node>*> shortenedPath)
{
	vector<Vertex<Node>*> caminho;
	Vertex<Node>* finalVertex = shortenedPath[shortenedPath.size() - 1];

	for (size_t i = 0; i < shortenedPath.size() - 1; i++) 
	{
		caminho.push_back(shortenedPath[i]);

		for (auto edge : shortenedPath[i]->adj) 
		{
			if (edge.dest == shortenedPath[i + 1])
				caminho.insert(caminho.end(), edge.hidden.begin(), edge.hidden.end());
		}
	}

	while (caminho.size() > 0 && caminho[caminho.size() - 1] != finalVertex) 
	{
		caminho.pop_back();
	}

	return caminho;
}

void MyGraph::floydWarshallSP()
{
	cout << "Iniciando algoritmo Floyd-Warshall para caminho-mais-curto...." << endl;
	finalGraph->floydWarshallShortestPath();
	cout << "...Processo completado." << endl;
}

void MyGraph::preProcess()
{
	finalGraph = graph->preProcessGraph();
}

void MyGraph::recalculateDistContainers(int currentVertexPos, bool isSort)
{
	Vertex<Node>* tempVertex;
	for (auto contentor : contentores) 
	{
		cout << "->DIST: " << contentor->getNode() << endl;
		tempVertex = finalGraph->getVertex(contentor->getNode());
		contentor->setIndex(tempVertex->posAtVec);
		contentor->setDistance(finalGraph->dist[currentVertexPos][contentor->getIndex()]);
	}

	cout << "Distancias recalculadas...." << endl;

	if (isSort && contentores.size() > 0)
		sort(contentores.begin(), contentores.end(), compareContainer());

	cout << "Sorting completo." << endl;
}

vector<Vertex<Node>*> MyGraph::genOneTruck_NContainers(Camiao * c, Estacao * e) {
	
	vector<Vertex<Node> * > result, temp;

	pair<Vertex<Node>*, Vertex<Node>*> nodes = finalGraph->getTwoVertexs(c->getGarage(), e->getNode());
	Vertex<Node>* garage = nodes.first;
	Vertex<Node>* station = nodes.second;
	int currentVertex = garage->posAtVec;

	recalculateDistContainers(currentVertex, true);
	
	Vertex<Node> * current = (*finalGraph)(currentVertex), * next = (*finalGraph)(contentores[0]->index);
	result = finalGraph->getfloydWarshallPath(current, next);
	
	while (contentores.size() > 0 && c->getCapacity() >= contentores[0]->getCapacity()) {
		
		c->addCapacity(-contentores[0]->getCapacity());
		cout << "added container(1): "; 
		cout << contentores[0]->getNode() << endl;
		contentores.erase(contentores.begin());
		if (contentores.size() == 0)
			break;
		recalculateDistContainers(current->posAtVec, true);
		cout << "CONTAINERS: " << contentores.size()  << endl;
		current = next;
		next = (*finalGraph)(contentores[0]->index);
		temp = finalGraph->getfloydWarshallPath(current, next);
		for (size_t i = 0; i < contentores.size(); i++) {
			if (temp.size() > 0 
				&& find(temp.begin(), temp.end(), (*finalGraph)(contentores[i]->index)) != temp.end()
				&& c->getCapacity() >= contentores[i]->getCapacity()) {
					c->addCapacity(-contentores[i]->getCapacity());
					cout << "added container: ";
					cout << contentores[i]->getNode() << endl;
					contentores.erase(contentores.begin()+i);
					cout << "ERASED: " << i << endl;
					i--;
			} 
		}
		result.insert(result.end(), temp.begin() + 1, temp.end());
	}

	temp = finalGraph->getfloydWarshallPath(next, station);
	result.insert(result.end(), temp.begin() + 1, temp.end());
	result.push_back(station);


	return result;
}

vector<vector<Vertex<Node>*>> MyGraph::genNTrucks_NContainers(Estacao * e, int N) {
	
	vector<vector<Vertex<Node>*>> result;

	Camiao * t = camioes[0];
	while (contentores.size() > 0) {
		cout << "TRUCK" << contentores.size() << endl;
		t->setCapacity(N);
		result.push_back(genOneTruck_NContainers(t, e));
	}
	//todo deal with last container

	return result;
}
