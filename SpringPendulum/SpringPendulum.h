#ifndef SPRINGPENDULUM_H
#define SPRINGPENDULUM_H

#include "Object.h"
#include "Config.h"
#include "Convert.h"
#include "MouseManager.h"
#include "KeyboardManager.h"


using namespace MOUSE;
using namespace KEYBOARD;

class SpringPendulum : public Object
{

public :
	void init();
	void setRestPosition();
	void updateStateSpring();
	void rotateSpring(float angle);
	void render(sf::RenderWindow& window);
	void update();
	void process(sf::RenderWindow & window);
	void updateSpringsAngle(float delta_angle);
	void updateSpringsAngle1(float angle);
	void drawSprings(sf::RenderWindow& window);
	void reset();

	void applyForce(Vector2D force);

private:
	float rest_length;
	Vector2D anchor;
	float springs_width;
	float angle_spring ;
	float angle_rotate;
	float delta_angle_spring;
	Vector2D contact;
	Vector2D gravity;

	float a_angle_rotate;
	float v_angle_rotate;

	float thickness ;
	float old_angle;

	// ===========

	sf::CircleShape ball;
	sf::RectangleShape bound;
	std::vector<sf::VertexArray> texture_springs;

	//============

	float k;

};

#endif // !SPRINGPENDULUM_H




