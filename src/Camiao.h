#pragma once

#include "Node.h"

using std::string;

class Camiao : public Node {

private:

    Node garage;
	int id;
    bool full;//whether or not truck is full
    float capacity; //total capacity of truck
	float volumeOccupied; //total volume Occupied
	float percentageOccupied; //percentage of truck capacity occupied
    char type; //type of residue

public:
    Camiao(int id, float capacity, char type, Node garage);
	Camiao(Node garagem, float capacity, char type = 'i');

    //getters
    int getId();
    float getCapacity();
	float getVolumeOccupied();
	float getPercentageOccupied();
    char getType();
    bool isFull();
	Node getGarage();

    //setters
	void setVolumeOccupied(float volumeOccupied);
    void addCapacity(float capacity);
    void setFull(bool full);
    void setCapacity(float capacity);
    void setType(char type);
    void setGarage(Node garage);
};

