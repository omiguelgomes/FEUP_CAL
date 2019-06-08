#include <iostream>
#include <cmath>
#include "Node.h"



Node::Node(int id, double lat, double lon)
{
    this->id = id;
    latitude = lat;
    longitude = lon;
}

Node::Node()
{
    Node(0, 0, 0);
}

double Node::getLat() const
{
    return latitude;
}

double Node::getLon() const
{
    return longitude;
}

int Node::getID() const
{
    return id;
}

void Node::setLat(double lat)
{
    this->latitude = lat;
}

void Node::setLon(double lon)
{
    this->longitude = lon;
}

void Node::setId(int id)
{
    this->id = id;
}

double Node::distance(Node b)
{
	double u, v;
	u = sin((b.getLat() - latitude) / 2);
	v = sin((b.getLon() - longitude) / 2);

	return 1000 * 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(latitude) * cos(b.getLat()) * v * v));
}

bool Node::operator==(const Node &b)const
{
    return this->id == b.getID();
}

bool Node::operator!=(const Node &b) const
{
    return ! this->operator==(b);
}

ostream & operator << (ostream &s, const Node &node)
{
    s << "{id: " << node.id << ", lat: " << node.latitude << ", lon: " << node.longitude << "}";
    return s;
}