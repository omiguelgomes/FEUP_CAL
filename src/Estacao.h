#pragma once

#include "Node.h"

class Estacao : public Node {

public:

    Estacao();
    Estacao(int id, float lat, float lon);
	Estacao(Node n);

    Node getNode();
};



