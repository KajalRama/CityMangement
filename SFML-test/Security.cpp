#include "Security.h"

using namespace std;


Security::Security() : Tile() {
	safety = 0;
	employment = 0;
}
Security::Security(int safety, int employment, float height, float width, float gridX, float gridY, string textureFile,  int cost)
		 : Tile(height, width, gridX, gridY, textureFile, "security", cost){
	this->safety = safety;
	this->employment = employment;
}
int Security::getSafety() {
	return safety;
}
void Security::setSafety(int safety) {
	this->safety = safety;
}
int Security::getEmployment() {
	return employment;
}
void Security::setEmployment(int employment) {
	this->employment = employment;
}