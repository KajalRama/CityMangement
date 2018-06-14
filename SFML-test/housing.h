#ifndef HOUSING_H
#define EOUSING_H
#include "Tile.h"
#include <iostream>

using namespace std;

class Housing : public Tile {

public:
	Housing();   //default constructor
	Housing(int population, int pollution, int employment, float height, float width, float gridX, float gridY, string textureFile,  int cost);  //parameterized constructor
	int getPopulation();
	void setPopulation(int population);
	void setSafety(int safety);
	int getPollution();
	void setPollution(int pollution);
	int getEmployment();
	void setEmployment(int employment);
private:
	int population;
	int pollution;
	int employment;
	int safety;
};


#endif