#pragma once

#include "Node.h"

#include <string>
#include <vector>

using std::string;
using std::ostream;
using std::vector;

class Road
{
public:
    Road(int id, Node * originNode, Node * destinyNode);
	// Road(string id);
    // Road();

    //getters
    int getId() const;
    Node * getOrigin() const;
    Node * getDestiny() const;

    //setters
    void setId(int id);
    void setOriginNode(Node * node);
    void setDestinyNode(Node * node);

    friend ostream& operator<<(ostream& os, const Road& r);
   

protected:
    int id;
	Node* originNode;
	Node* destinyNode;
};

