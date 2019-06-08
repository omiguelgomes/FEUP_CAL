#include "Contentor.h"

Contentor::Contentor() 
{
	capacity = 0;
	full = false;
    Node();
}

Contentor::Contentor(int id, float lat, float lon) {

    Node(id, lat, lon);
}

Contentor::Contentor(Node n, bool full, float capacity, char type) : full(full), capacity(capacity), type(type) {
	id = n.getID();
	latitude = n.getLat();
	longitude = n.getLon();
}

float Contentor::getCapacity() {
    return capacity;
}

char Contentor::getType() {
    return type;
}

double Contentor::getDistance() {
    return dist;
}

int Contentor::getIndex() {
    return index;
}

Node Contentor::getNode() {
    return Node(id, latitude, longitude);
}

void Contentor::setFull(bool full) {
    this->full = full;
}

void Contentor::setCapacity(float capacity) {
    this->capacity = capacity;
}

void Contentor::setType(char type) {
    this->type = type;
}

void Contentor::setIndex(int ind)
{
	index = ind;
}

void Contentor::setDistance(int dist)
{
	this->dist = dist;
}

bool Contentor::isFull() {
    return full;
}

