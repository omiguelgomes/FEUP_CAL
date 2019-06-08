#pragma once

#include <string>

using std::string;
using std::ostream;

#define PI 3.14159265358979323846
#define earthRadiusKm 6371.0

class Node
{
public:
    Node(int id, double lat, double lon); //std constructor to initialize node
    Node(); //default

    //getters
    double getLat() const;
    double getLon() const;
    int getID() const;

    //setters
    void setLat(double lat);
    void setLon(double lon);
    void setId(int id);

    double distance (Node b); //distance between two nodes

    //op. overloads
    bool operator== (const Node & b) const;
    bool operator!= (const Node & b) const;
    friend ostream & operator<< (ostream & s, const Node & node);

protected:
    double latitude, longitude;
    int id;
};