
#ifndef Jobs_h
#define Jobs_h

#include "Tile.h"
#include <iostream>

using namespace std;

class Jobs : public Tile {

public:
	Jobs();   //default constructor
	Jobs(int income, int safety, int pollution, int employment, float height, float width, float gridX, float gridY, string textureFile,  int cost);   //parameterized constructor
	int getIncome();     
	void setIncome(int income) ;   
	int getSafety();    
	void setSafety(int safety) ;  
	int getPollution();
	void setPollution(int pollution) ;
	int getEmployment();
	void setEmployment(int employment);

private:
	int income;
	int safety;
	int pollution;
	int employment;
};
#endif
