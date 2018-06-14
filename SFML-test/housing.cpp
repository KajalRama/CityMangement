#include "housing.h"
#include <iostream>

//default constructor
Housing::Housing() : Housing(0, 0, 0, 0, 0, 0, 0, "",0) {};

Housing::Housing(int population, int pollution, int employment, float height, float width, float gridX, float gridY, string textureFile,  int cost)            //parameterized constructor
	: Tile(height, width, gridX, gridY, textureFile,  "housing", cost)          //calls the base constructor
{
	
	this->population = population;
	this->pollution = pollution;
	this->employment = employment;
}

int Housing::getPopulation()              //get population
{
	return population;
}

void Housing::setSafety(int safety){     //set safety
	this->safety = safety;
}

int Housing::getPollution()           //get  pollution
{
	return pollution;
}

void Housing::setPollution(int pollution){      //set pollution
	this->pollution = pollution;
}
void Housing::setPopulation(int population) {      //set population
	this->population = population;
}

int Housing::getEmployment()            //get employment
{
	return employment;
}

void Housing::setEmployment(int employment){            //set employment
	this->employment = employment;
}
