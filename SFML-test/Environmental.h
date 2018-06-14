#pragma once
#ifndef Environmental_h
#define Environmental_h
#include "Tile.h"
#include <iostream>

using namespace std;

class Environmental : public Tile {

public:
	Environmental(); //default constructor
	Environmental(int safety, int pollution, int employment, float height, float width, float gridX, float gridY, string textureFile, int cost); //parameterized constructor
	int getSafety();
	void setSafety(int safety);
	int getPollution();
	void setPollution(int pollution);
	int getEmployment();
	void setEmployment(int employment);
private:
	int safety;
	int pollution;
	int employment;
};


#endif

