#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector2D.h"
#include "MouseManager.h"
#include "FontManager.h"


using namespace MOUSE;

class Bar
{

public:
	Bar(Vector2D loc =Vector2D(0,0), std::string label ="" ,float min =0.f ,float max =10.f);
	void render(sf::RenderWindow& windows);
	void process(sf::RenderWindow& windows);
	void init(Vector2D loc = Vector2D(0, 0), std::string label = "", float min = 0.f, float max = 10.f);
	void update();
private:
	float value;
	float max;
	float min;
	float unit_length;
	float length_bar;
	std::string lable;
	Vector2D location;

	sf::VertexArray bar;
	sf::RectangleShape wheel;
	sf::Text text;
};



#endif //!BAR