#include "Tile.h"
#include <iostream>

using namespace std;

Tile::Tile() {              //tile constructor sets initial value
	height = 0;
	width = 0;
	gridX = 0;
	gridY = 0;
	tileType = "N";
	cost = 0;
}
Tile::Tile(float height, float width, float gridX, float gridY, string textureFile, string tileType, int cost) {    //parameterized constructor
	this->height = height;
	this->width = width;
	this->gridX = gridX;
	this->gridY = gridY;
	this->cost = cost;
	this->tileType = tileType;
	this->texture = texture;
	
	if (!texture.loadFromFile(textureFile)) {
		cout << "Error Loading Texture: " << textureFile << endl;
	}
	else {
		shape.setTexture(&texture);
	}
	
	shape.setSize(sf::Vector2f(height, width));
	shape.setPosition(gridX, gridY);
	
}
float Tile::getHeight() {        //get the height of the tile
	return height;
}
void Tile::setHeight(float height) {    //set the height of the tile
	this->height = height;
}
float Tile::getWidth() {       //get the width of the tile
	return width;
} 
void Tile::setWidth(float width) {       //set the width of the tile
	this->width = width;
}
float Tile::getX() {        //get the X position of the grid
	return gridX;
}
void Tile::setX(float x) {     //set the X position of the grid
	gridX = x;
}
float Tile::getY() {      //get the Y position of the game
	return gridY;
}
void Tile::setY(float y) {      //set the Y position of the game
	gridY = y;
}
sf::RectangleShape Tile::getShape() {       //get the shape of the tile
	return shape;
}
void Tile::setTexture(string textureFile) {     //set the texture of the tile
	if (!texture.loadFromFile(textureFile)) {
		cout << "Error Loading " << textureFile << endl;
	}
	shape.setTexture(&texture);
}
int Tile::getCost() {          //get the cost
	return cost;
}
void Tile::setCost(int cost) {   //set the cost
	this->cost = cost;
}

string Tile::getType() const {    //get the tile type
	return tileType;
}

void Tile::setColor(sf::Color color) {       //set the color
	shape.setFillColor(color);
}