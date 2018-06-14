#include "Jobs.h"
#include <iostream>
using namespace std;

Jobs::Jobs() : Tile() {           //default  constructor
	income = 0;
	safety = 0;
	pollution = 0;
	employment = 0;
}
Jobs::Jobs(int income, int safety, int pollution, int employment, float height, float width, float gridX, float gridY, string textureFile,  int cost)           //parameterized constructor
	 : Tile(height, width, gridX, gridY, textureFile, "jobs", cost) 
{
	this->income = income;
	this->safety = safety;
	this->pollution = pollution;
	this->employment = employment;
}
int Jobs::getIncome()    //get the income
{
	return income;
}
void Jobs::setIncome(int income)        //set the income
{
	this->income = income;
}
int Jobs::getSafety() {             //get safety
	return safety;
}
void Jobs::setSafety(int safety) {         //set safety
	this->safety = safety;
}
int Jobs::getPollution() {             //get pollution
	return pollution;
}
void Jobs::setPollution(int pollution) {           //set pollution
	this->pollution = pollution;
}
int Jobs::getEmployment() {               //get employment
	return employment;
}
void Jobs::setEmployment(int employment) {           //set employment
	this->employment = employment;
}
