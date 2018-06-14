#pragma once

#ifndef TRANSIT_H
#define TRANSIT_H

#include "Tile.h"
#include <iostream>

using namespace std;

class Transit : public Tile {

public:
	Transit();    //default constructor
	Transit(int transportation, int safety,int pollution, int accessibility, float height, float width, float gridX, float gridY, string textureFile, int cost);   //parameterized constructor
	int getTransportation();
	void setTransportation(int transportation);
	int getSafety();
	void setSafety(int safety);
	int getPollution();
	void setPollution(int pollution);
	int getAccessibility();
	void setAccessibility(int employment);

private:
	int transportation;
	int safety;
	int pollution;
	int accessibility;



};


#endif
