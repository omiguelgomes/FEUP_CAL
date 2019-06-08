#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include <time.h>
#include <list>
#include <chrono>
#include <iomanip>

#include "Parser.h"
#include "Contentor.h"
#include "Estacao.h"
#include "Graph.h"
#include "Node.h"
#include "Road.h"
#include "MyGraph.h"

using namespace std;

chrono::time_point<chrono::system_clock> startingTime;
chrono::duration<double> diff;

double getDist(vector<Node> nodes)
{
	double dist = 0;
	if (nodes.size() == 0)
		return dist;
	for (size_t i = 0; i < nodes.size() - 1; i++) {
		dist += nodes[i].distance(nodes[i + 1]);
	}
	return dist;
}

int randBetween(int min, int max) 
{
	return min + (rand() % (int)(max - min + 1));
}

int randDiff(int min, int max, vector<int> dif) 
{
	int res = randBetween(min, max);
	while (find(dif.begin(), dif.end(), res) != dif.end())
		res = randBetween(min, max);
	return res;
}

void startRecordingTime() 
{
	startingTime = chrono::system_clock::now();
}

void stopRecordingTime(size_t nodes, string name) 
{
	diff = chrono::system_clock::now() - startingTime;
	cout << "TIME: " << nodes << " " << diff.count() << "(" << name << ")" << endl;
}

bool connectivity(list <Contentor> cont, Graph<Node>* gr, Node initial);

vector<Node> oneTruck_NContainers(MyGraph * graph, Camiao * c, Estacao * e)
{
	vector<Node> res;

	cout << "Estacao de recolha: " << c->getGarage().getID() << endl << "Contentores: " << graph->getContentores().size()
		<< endl << "Estacao: " << e->getID() << endl;

	vector<Contentor* > copia = graph->getContentores();
	vector<Vertex<Node>*> resolucao = graph->genOneTruck_NContainers(c, e); //fazer funcao

	graph->setContentores(copia);
	resolucao = graph->backPreProcess(resolucao);
	
	res = Graph<Node>::getInfoFromVector(resolucao);
	for (auto node : res)
	{
		cout << ">>"  << node.getID();
	}

	cout << endl;
	cout << "Distancia" << getDist(res);

	return res;
}

vector<Node> oneTruck_NContainers_helper (MyGraph* grafo, int numContentores)
{
	if (grafo->getGraph()->getNumVertex() <= numContentores + 2)
	{
		cerr << "Nao existem nos suficientes para correr o algoritmo!" << endl;
		return vector<Node>();
	}

	int rand_camiao, rand_est;
	vector<int> diffs;
	rand_camiao = randBetween(1, grafo->getGraph()->getNumVertex() - 1);
	diffs.push_back(rand_camiao);
	rand_est = randDiff(0, grafo->getGraph()->getNumVertex() - 1, diffs);
	diffs.push_back(rand_est);

	Camiao* c = new Camiao((*grafo->getGraph())(rand_camiao)->getInfo(), 0, 'i');
	Estacao * e = new Estacao ((*grafo->getGraph())(rand_est)->getInfo());
	grafo->getCamioes().clear();
	grafo->addTruck(c);
	grafo->getEstacoes().clear();
	grafo->addStation(e);

	grafo->getContentores().clear();
	int n = randDiff(0, grafo->getGraph()->getNumVertex() - 1, diffs);
	diffs.push_back(n);

	for (int i = 0; i < numContentores; i++) {
		n = randDiff(0, grafo->getGraph()->getNumVertex() - 1, diffs);
		diffs.push_back(n);
		cout << "Contentor: " << (*grafo->getGraph())(n)->getInfo() << endl;
		grafo->addContainer(new Contentor((*grafo->getGraph())(n)->getInfo(), true, 0, 'i'));
	}

	startRecordingTime();
	auto temp = oneTruck_NContainers(grafo, c, e);
	stopRecordingTime(grafo->getGraph()->getNumVertex(), "Um camiao, multiplos contentores -> NearestNeighbour (NN)");
	return temp;
}

vector<vector<Node>> NTrucks_NContainers(MyGraph* grafo, Camiao* c, Estacao* e)
{
	vector<vector<Node>> res;

	cout << "Estacao de recolha: " << c->getGarage().getID() << endl << "Contentores: " << grafo->getContentores().size()
		<< endl << "Estacao: " << e->getID() << endl;

	vector<Contentor *> copia = grafo->getContentores();
	vector<vector<Vertex<Node>*>> resolucao = grafo->genNTrucks_NContainers(e, 10); //fazer funcao

	grafo->setContentores(copia);
	for (auto & truckPath : resolucao)
		truckPath = grafo->backPreProcess(truckPath);

	for (auto truckPath : resolucao)
		res.push_back(Graph<Node>::getInfoFromVector(truckPath));

	double totalDist = 0;
	for (auto path : res) 
	{
		totalDist += getDist(path);

		for (auto node : path)
			cout << ">>" << node.getID();

		cout << endl;
	}

	cout << "Distancia percorrida total: " << totalDist << endl;
	cout << "Numero de camioes usados:   " << res.size() << endl;

	return res;
}

vector<vector<Node>> NTrucks_NContainers_helper(MyGraph* grafo, int numContentores, float tamanhosC)
{
	if (grafo->getGraph()->getNumVertex() <= numContentores + 2)
	{
		cerr << "Nao existem nos suficientes para correr o algoritmo!" << endl;
		return vector<vector<Node>>();
	}

	int rand_camiao, rand_est;
	vector<int> diffs;
	rand_camiao = randBetween(0, grafo->getGraph()->getNumVertex() - 1);
	diffs.push_back(rand_camiao);
	rand_est = randDiff(0, grafo->getGraph()->getNumVertex() - 1, diffs);
	diffs.push_back(rand_est);

	Camiao * c = new Camiao((*grafo->getGraph())(rand_camiao)->getInfo(), 10, 'i');
	Estacao * e = new Estacao ((*grafo->getGraph())(rand_est)->getInfo());
	grafo->getCamioes().clear();
	grafo->addTruck(c);
	grafo->getEstacoes().clear();
	grafo->addStation(e);

	grafo->getContentores().clear();
	int n = randDiff(0, grafo->getGraph()->getNumVertex() - 1, diffs);
	diffs.push_back(n);

	for (int i = 0; i < numContentores; i++) {
		n = randDiff(0, grafo->getGraph()->getNumVertex() - 1, diffs);
		diffs.push_back(n);
		cout << "Container: " << (*grafo->getGraph())(n)->getInfo() << endl;
		grafo->addContainer(new Contentor ((*grafo->getGraph())(n)->getInfo(), true, tamanhosC, 'i'));
	}

	return NTrucks_NContainers(grafo, c, e);
}

int main()
{

	srand(time(NULL));
	cout << "Funcionalidades: " << endl;
	cout << "Display de todos os nos: 'A'" << endl;
	cout << "Outras funcionalidades: [qualquer tecla]" << endl;
	char c;
	cin >> c;

	vector<Contentor*> contentores;
	MyGraph* grafo = new MyGraph("data/nodes.txt", "data/edges.txt", "data/tag.txt");

	startRecordingTime();	
	grafo->preProcess();
	stopRecordingTime(grafo->getGraph()->getNumVertex(), "pre-processamento do grafo");

	vector<Vertex<Node>*> temp;
	temp = grafo->getFinalGraph()->getVertexSet();
	vector<Node> vertexes;
	if (c == 'a' || c == 'A')
	{
		for (auto node : temp)
		{
			vertexes.push_back(node->getInfo());
		}

		for (auto v : vertexes)
		{
			cout << v << endl;
		}
	}

	startRecordingTime();
	grafo->floydWarshallSP();
	stopRecordingTime(grafo->getGraph()->getNumVertex(), "floydWarshallShortestPath");

	cout << "Tamanho do grafo: " << temp.size() << endl;

	vector<vector<Node>> paths;
	string command = "";
	do {
		cin.clear();
		cout << "COMMAND: " << endl;
		cout << "   1  -> One truck  N   Containers" << endl;
		cout << "   2  -> N   trucks N   Containers" << endl;
		cout << "   3  -> Check graph connectivity" << endl;
		cout << "   Anything else -> Stop the program" << endl;
		cin >> command;

		int numContentores;

		if (command == "1")
		{
			cout << "Introduza o numero de contentores:";
			cin >> numContentores;
			paths.push_back(oneTruck_NContainers_helper(grafo, numContentores));
		}
		else if (command == "2")
		{
			cout << "Introduza o numero de contentores:";
			cin >> numContentores;
			paths = NTrucks_NContainers_helper(grafo, numContentores, 5);
		}
		else if (command == "3")
		{
			list<Contentor> cont;
			for (auto c : grafo->getContentores())
				cont.push_back(*c);
			connectivity(cont, grafo->getFinalGraph(), grafo->getCamioes()[0]->getGarage());
			cin >> numContentores;
			paths = NTrucks_NContainers_helper(grafo, numContentores, 5);
		}
		else
		{
			break;
		}

		for (int i = 0; i< paths.size(); i++)
		{
			for (int j = 0; j < paths[i].size(); j++)
			{
				cout << paths[i][j] << endl;
			}
		}

	} while (true);


	cout << "Processo completo" << endl;

	return 0;
}

bool connectivity(list <Contentor> cont, Graph<Node>* gr, Node initial)
{
	vector<Node> connected = gr->bfs(gr->getVertex(initial));
	gr->resetVisited();

	cout << endl << "Verificar conectividade do grafo..." << endl;

	list<Contentor>::iterator it;
	for (it = cont.begin(); it != cont.end(); it++) 
	{
		for (unsigned i = 0; i < connected.size(); i++) 
		{
			if (connected[i] == (*it).getNode()) 
			{
				break;
			}

			if (i == connected.size()) 
			{
				stringstream ss;
				string id;

				ss << (*it).getNode().getID();
				id = ss.str();

				cout << "Erro de conectividade no Contentor" + id + " ! Este contentor nao pode ser alcancado!" << endl;

				getchar();
				return false;
			}
		}

		list<Contentor>::iterator ita;
		for (ita = cont.begin(); ita != cont.end(); ita++) 
		{
			if (it != ita) {
				vector<Node> connected2 = gr->bfs(gr->getVertex((*it).getNode()));
				gr->resetVisited();

				for (unsigned int i = 0; i <= connected2.size(); i++) 
				{
					if (connected2[i] == (*ita).getNode())
					{
						break;
					}

					if (i == connected2.size())
					{
						stringstream ss1, ss2;
						string id_s, id_d;

						ss1 << (*it).getNode().getID();
						id_s = ss1.str();

						ss2 << (*ita).getNode().getID();
						id_d = ss2.str();

						cout << "Contentor " + id_d + "inalcancavel desde" + id_s + "!" << endl;

						return false;
					}
				}
			}
		}
	}
	cout << "Teste terminado." << endl;

	return true;
}