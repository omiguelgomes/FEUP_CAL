//
// Created by eddyc on 15/05/2019.
//

#include "Camiao.h"

Camiao::Camiao(int id, float capacity, char type, Node garage) {

	this->id = id;
	this->capacity = capacity;
	this->type = type;
	this->volumeOccupied = 0;
	this->percentageOccupied = 0;
	this->full = false;
	this->garage = garage;
}

Camiao::Camiao(Node garagem, float capacity, char type) 
	:garage(garagem), 
	capacity(capacity), 
	type(type) 
{}

//Getters
int Camiao::getId() {
	return this->id;
}

float Camiao::getCapacity() {
    return this->capacity;
}

float Camiao::getVolumeOccupied() {
	return this->volumeOccupied;
}

float Camiao::getPercentageOccupied() {
	return this->percentageOccupied;
}

char Camiao::getType() {
    return this->type;
}

bool Camiao::isFull() {
	return full;
}

//Setters

void Camiao::setVolumeOccupied(float volumeOccupied) {
	this->volumeOccupied = volumeOccupied;
}

void Camiao::setFull(bool full) {
    this->full = full;
}

void Camiao::setCapacity(float capacity) {
    this->capacity = capacity;
}

void Camiao::addCapacity(float capacity) {
	this->capacity += capacity;
}

void Camiao::setType(char type) {
    this->type = type;
}

Node Camiao::getGarage() {
    return this->garage;
}

void Camiao::setGarage(Node garage) {
    this->garage = garage;
}

