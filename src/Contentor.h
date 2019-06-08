#pragma once
#include "Node.h"

using std::string;

class Contentor : public Node {

private:
    bool full;      //whether or not container is full
    float capacity; //total capacity of container
    char type;      //type of residue
    double dist;    //distance to station
    

public:
    int index;      //index of container on vector of container     
    Contentor();
    Contentor(int id, float lat, float lon);
	Contentor(Node n, bool full, float capacity, char type);

    //getters
    float getCapacity();
    char getType();
    double getDistance();
    int getIndex();
    Node getNode();

    //setters
    void setFull(bool full);
    void setCapacity(float capacity);
    void setType(char type);
	void setIndex(int ind);
	void setDistance(int dist);

    bool isFull();
};

struct compareContainer {
    bool const operator()(Contentor * a, Contentor * b) const {
        return a->getDistance() < b->getDistance();
    }
};
