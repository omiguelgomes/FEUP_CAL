#include <iostream>
#include "Road.h"


Road::Road(int id, Node * originNode, Node * destinyNode)
{
    this->id = id;

	this->originNode = originNode;
	this->destinyNode = destinyNode;
}


//Getters
int Road::getId() const { return this->id; }

Node* Road::getOrigin() const { return this->originNode; }

Node* Road::getDestiny() const { return this->destinyNode; }


//Setters
void Road::setId(int id) { this->id = id; }

void Road::setOriginNode(Node* node) { this->originNode = node; }

void Road::setDestinyNode(Node* node) { this->destinyNode = node; }

ostream & operator<<(ostream & os, const Road & r) {
	os << "{id: "<< r.getId() << ", origin: " << r.getOrigin()  << ", destination: " << r.getDestiny() << "}";
	return os;
}