#include "ImageButton.h"
#include <string>
#include <iostream>

ImageButton::ImageButton(std::string file, float size, float x, float y) {    //parameterized constructor
	this->file = file;
	if (!texture.loadFromFile(file)) {
		std::cout << "Could not find file: " << std::endl;
	}

	shape.setSize(sf::Vector2f(size, size));
	shape.setPosition(sf::Vector2f(x, y));
	shape.setTexture(&texture);
}

sf::RectangleShape ImageButton::getShape() const {           //get the shape of the button
	return shape;
}
bool ImageButton::contains(int x, int y) {                      //check if the button is being clicked
	return shape.getGlobalBounds().contains((float)x, (float)y);
}

void ImageButton::makeActive() {            //make the button active
	active = true;
	shape.setFillColor(sf::Color::Blue);
}
void ImageButton::unmakeActive() {            //make the button unactive
	if (active != false) {
		active = false;
		shape.setTexture(&texture);
		shape.setFillColor(sf::Color::White);
	}
}
float ImageButton::getShapeSize() const {                 //get the size of the shape
	return shape.getSize().x;
}
float ImageButton::getShapeX() const {        //get X position
	return shape.getPosition().x;
}
float ImageButton::getShapeY() const {        //get Y position
	return shape.getPosition().y;
}
void ImageButton::setTexture(std::string file) {          //set the texture
	this->file = file; 
	if (!texture.loadFromFile(file)) {
		std::cout << "Could not find file: " << std::endl;
	}
}