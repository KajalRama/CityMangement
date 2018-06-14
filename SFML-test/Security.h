#pragma once

#ifndef SECURITY_H
#define SECURITY_H

#include "Tile.h"
#include <iostream>

using namespace std;

class Security : public Tile{

public:
	Security();    //default constructor
	Security(int safety, int employment, float height, float width, float gridX, float gridY, string textureFile, int cost); //parameterized constructor
	int getSafety();
	void setSafety(int safety);
	int getEmployment();
	void setEmployment(int employment);

private:
	int safety;
	int employment;



};


#endif
