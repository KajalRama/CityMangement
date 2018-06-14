#include "Transit.h"


Transit::Transit() : Tile() {         //default constructor
	transportation = 0;
	safety = 0;
	pollution = 0;
	accessibility = 0;
}
Transit::Transit(int transportation, int safety, int pollution, int accessibility, float height, float width, float gridX, float gridY, string textureFile,  int cost)            //parameterized constructor
        :Tile(height, width, gridX, gridY, textureFile, "transit", cost){          //call to the base class constructor
	this->transportation = transportation;
	this->safety = safety;
	this->pollution = pollution;
	this->accessibility = accessibility;
}
int Transit::getTransportation() {            //get transportation
	return transportation;
}
void Transit::setTransportation(int transportation) {     //set transportation
	this->transportation = transportation;
}
int Transit::getSafety() {       //get safety
	return safety;
}
void Transit::setSafety(int safety) {           //set safety
	this->safety = safety;
}
int Transit::getPollution() {          //get pollution
	return pollution;
}
void Transit::setPollution(int pollution) {         //set pollution
	this->pollution = pollution;
}
int Transit::getAccessibility() {             //get accessibility
	return accessibility;
}
void Transit::setAccessibility(int employment) {       //set accessibility
	this->accessibility = accessibility;
}