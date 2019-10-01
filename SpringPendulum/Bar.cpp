#include "Bar.h"

Bar::Bar(Vector2D loc , std::string label ,float min , float max)
{

	this->value = 0.f;
	this->max = max;
	this->lable = label;
	this->location = loc;


	bar = sf::VertexArray(sf::Lines, 2);
	bar[0].position = this->location.toVec2f();
	bar[1].position = this->location.movePoint(0.f, max).toVec2f();


	wheel.setSize(sf::Vector2f(20.f, 30.f));
	wheel.setPosition((location.movePoint(0.f, value) - Vector2D(wheel.getSize().x / 2, wheel.getSize().y / 2)).toVec2f());


}

void Bar::render(sf::RenderWindow& windows)
{
	windows.draw(wheel);
	windows.draw(text);

	windows.draw(bar);
}

void Bar::process(sf::RenderWindow& windows)
{
	Mouse& mouse = mouse.getIntance();

	if (mouse.getStateMouse(MOUSE_B::LEFT)) {
		auto bound_wheel = wheel.getGlobalBounds();

		sf::Vector2f mouse_c(mouse.getMouseWindow(windows));
		if(mouse.)
		else if (bound_wheel.contains(mouse_c)) {
			value = (Vector2D(mouse_c.x , location.y) - location).mag();
			if (value > max) value = max;
			else if (value < min) value = min;
		}
	}
}

void Bar::init(Vector2D loc, std::string label, float min ,float max)
{
	this->value = 0.f;
	this->max = max;
	this->lable = label;
	this->location = loc;


	bar = sf::VertexArray(sf::Lines, 2);
	bar[0].position = this->location.toVec2f();
	bar[1].position = this->location.movePoint(0.f, max).toVec2f();


	wheel.setSize(sf::Vector2f(8.f, 15.f));
	wheel.setPosition((location.movePoint(0.f, value) - Vector2D(wheel.getSize().x / 2, wheel.getSize().y / 2)).toVec2f());

	FontManager::getInstance().uploadResource("Roboto");

	sf::Font *font = FontManager::getInstance().getResource("Roboto");
	
	text.setCharacterSize(11);
	text.setFont(*font);
	text.setString(this->lable);
	

	auto bound_text = text.getGlobalBounds();
	std::cout << bound_text.width << " : " << bound_text.height << std::endl;
	text.setPosition((this->location - Vector2D(bound_text.width +10, bound_text.height )).toVec2f());


}

void Bar::update()
{
	wheel.setPosition((location.movePoint(0.f, value) - Vector2D(wheel.getSize().x / 2, wheel.getSize().y / 2)).toVec2f());
}
