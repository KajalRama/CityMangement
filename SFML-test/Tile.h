#pragma once

#ifndef TILE_H
#define TILE_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

class Tile {
public:
	Tile();      //default constructor
	Tile(float height, float width, float gridX, float gridY, string textureFile, string type, int cost);         //parameterized constructor
	float getHeight();
	void setHeight(float height);
	float getWidth();
	void setWidth(float width);
	float getX();
	void setX(float gridX);
	float getY();
	void setY(float gridY);	
	sf::RectangleShape getShape();
	void setTexture(string textureFile);
	int getCost();
	void setCost(int cost);
	string getType() const;
	void setColor(sf::Color color);
private:
	float height;
	float width;
	float gridX;
	float gridY;
	sf::Texture texture;
	sf::RectangleShape shape;
	int cost;
	string tileType;
	
};
#endif // !TILE_H

