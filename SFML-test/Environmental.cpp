#include "Environmental.h"
#include <iostream>
using namespace std;

Environmental::Environmental() : Tile() {    //default constructor
	safety = 0;
	pollution = 0;
	employment = 0;
}
Environmental::Environmental(int safety, int pollution, int employment, float height, float width, float gridX, float gridY, string textureFile, int cost)       //parameterized constructor
	: Tile(height, width, gridX, gridY, textureFile,  "environmental", cost)        //call to the constructor of the base class
{
	this->safety = safety;
	this->pollution = pollution;
	this->employment = employment;
}
int Environmental::getSafety() {        //get safety
	return safety;
}
void Environmental::setSafety(int safety) {   //set safety
	this->safety = safety;
}
int Environmental::getPollution() {   ///get pollution
	return pollution;
}
void Environmental::setPollution(int pollution) {   //set pollution
	this->pollution = pollution;
}
int Environmental::getEmployment() {     //get employment
	return employment;
}
void Environmental::setEmployment(int employment) {     //set employment
	this->employment = employment;
}
