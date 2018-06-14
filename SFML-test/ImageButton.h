#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

/*****
* This handles the buttons for the city management game
* This is also just a modified version of the TextButton class from the fractal project
*****/

class ImageButton {
public:
	ImageButton(std::string file, float size, float x, float y);      //parameterized constructor

	void setTexture(std::string file);

	bool contains(int x, int y);
	void makeActive();
	void unmakeActive();

	float getShapeSize() const;
	float getShapeX() const;
	float getShapeY() const;
	sf::RectangleShape getShape()  const;
private:
	std::string file;
	sf::RectangleShape shape;
	sf::Texture texture;
	bool active;
};
#endif 