//
// Created by eddyc on 16/05/2019.
//

#include "Estacao.h"

Estacao::Estacao() {
    Node();
}

Estacao::Estacao(int id, float lat, float lon) {

    this->id = id;
    this->latitude = lat;
    this->longitude = lon;
}

Estacao::Estacao(Node n)
{
	id = n.getID();
	latitude = n.getLat();
	longitude = n.getLon();
}

Node Estacao::getNode() {
    return Node(id, latitude, longitude);
}