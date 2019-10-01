#include "SpringPendulum.h"

void SpringPendulum::init()
{
	this->anchor = Vector2D(SCREEN_WIDTH / 2, 100);
	this->rest_length = 200.f;
	this->springs_width = 20.f;
	this->angle_spring = 20.f;
	this->delta_angle_spring = 0.f;
	this->k = 0.02f;

	this->gravity = Vector2D(0, 0.1f);

	// init ball 
	ball.setFillColor(sf::Color(100, 100, 120));
	ball.setRadius(20);
	obj.mass = 1.f;
	angle_rotate = 0.f;
	a_angle_rotate = 0.f;
	v_angle_rotate = 0.f;

	thickness = 2;

	ball.setFillColor(sf::Color(100, 100, 100));
	ball.setPosition(200, 200);
	ball.setRadius(24);
	ball.setOutlineColor(sf::Color(200, 100, 120));
	ball.setOutlineThickness(thickness);
	
	//
	this->setRestPosition();

	
}

void SpringPendulum::setRestPosition()
{
	float temp = 0;
	unsigned int count = 0;

	sf::Vector2f origin_temp = anchor.toVec2f();

	float range_point_v = sinf(Convert::DegreeToRadius(angle_spring)) * springs_width;
	float range_point_h = cosf(Convert::DegreeToRadius(angle_spring)) * springs_width;
	

	rest_length = rest_length + (obj.mass * gravity.mag()) / k;

	while (temp < rest_length)
	{
		sf::VertexArray v_temp(sf::Lines, 2);
		v_temp[0].position = origin_temp;
		if (temp == 0) {
			v_temp[1].position = sf::Vector2f(origin_temp.x + range_point_h / 2,
				origin_temp.y + range_point_v);
		}
		else {
			v_temp[1].position = sf::Vector2f(origin_temp.x + range_point_h,
				origin_temp.y + range_point_v);
		}


		texture_springs.push_back(v_temp);

		sf::VertexArray v_temp1(sf::Lines, 2);
		v_temp1[0].position = v_temp[1].position;
		v_temp1[1].position = sf::Vector2f(anchor.x - range_point_h / 2,
			v_temp[0].position.y + 2 * range_point_v);

		texture_springs.push_back(v_temp1);

		origin_temp = v_temp1[1].position;

		temp += 2 * range_point_v;
	}
	sf::VertexArray v_temp(sf::Lines, 2);
	v_temp[0].position = origin_temp;
	v_temp[1].position = sf::Vector2f(anchor.x,
		origin_temp.y + range_point_v);
	texture_springs.push_back(v_temp);


	origin_temp = v_temp[1].position;
	obj.loc = Vector2D(texture_springs.back()[1].position.x - ball.getRadius()/ 2
		, texture_springs.back()[1].position.y);

	contact = anchor.movePoint(90 , rest_length);

	std::cout << rest_length << std::endl;
	
}


void SpringPendulum::rotateSpring(float angle)
{
	sf::Vector2f point_start = texture_springs[0][0].position;
	Vector2D temp;
	for (auto& i : texture_springs) {
		temp = i[1].position - i[0].position;
		i[0].position = point_start;
		point_start = i[1].position = i[0].position + temp.rotate(angle).toVec2f();
	}
}


void SpringPendulum::updateSpringsAngle(float delta_angle )
{
	bool check = false;
	sf::Vector2f point_start = texture_springs.at(0)[0].position;
	Vector2D temp;

	for (auto &i : texture_springs) {
		temp = i[1].position - i[0].position;
		i[0].position = point_start;

		point_start = (check) ? i[1].position = i[0].position + temp.rotate(Convert::DegreeToRadius(delta_angle)).toVec2f()
			: i[1].position = i[0].position + temp.rotate(Convert::DegreeToRadius(-delta_angle)).toVec2f();
		check = !check;
	}
}


void SpringPendulum::updateSpringsAngle1(float angle)
{
	bool check = true;
	unsigned int count = 0; 
	sf::Vector2f point_start = texture_springs.at(0)[0].position;
	for (auto& i : texture_springs) {
		i[0].position = point_start;
		if (check) {
			i[1].position = (!count || count+1 == texture_springs.size()) ? 
				Vector2D(point_start).movePoint(angle, springs_width / 2).toVec2f() :
				Vector2D(point_start).movePoint(angle, springs_width).toVec2f();
		}
		else {
			i[1].position = (texture_springs.size() ==count)?
				Vector2D(point_start).movePoint(float(PI - angle), springs_width/2).toVec2f():
				Vector2D(point_start).movePoint(float(PI - angle), springs_width).toVec2f();
		}
		point_start = i[1].position;
		check = !check;
		count++;
	}
}




void SpringPendulum::render(sf::RenderWindow& window)
{

	window.draw(ball);
	this->drawSprings(window);

}


void SpringPendulum::applyForce(Vector2D force)
{
	obj.acc += force / obj.mass;
}


void SpringPendulum::update()
{
	Vector2D force = contact - anchor;
	float stretch = force.mag() - rest_length;
	Vector2D m = force.normalize();
	Vector2D fs = m * stretch * k * (-1);


	this->applyForce(fs);
	float speed = obj.vec.mag();


	this->applyForce(gravity);
	this->applyForce(obj.vec.normalize() *speed * (-0.04f));

	obj.vec += obj.acc;
	obj.loc += obj.vec;
	
	this->updateStateSpring();

	obj.acc.reset();
	ball.setPosition(obj.loc.toVec2f());
}

void SpringPendulum::process(sf::RenderWindow& window)
{	
	Mouse& mouse = Mouse::getIntance();
	old_angle = angle_rotate;
	if (mouse.getStateMouse(MOUSE_B::LEFT)) {
		auto mouse_c = sf::Vector2f( mouse.getMouseWindow(window));
		auto bound_ball = ball.getGlobalBounds();

		auto size = ball.getRadius();
		if (bound_ball.contains(mouse_c.x, mouse_c.y)) {
			this->reset();
			angle_rotate = (Vector2D(mouse_c) - anchor).angle() - float(PI / 2);
			contact = Vector2D(mouse_c).movePoint(float(angle_rotate - PI / 2), (size + thickness));
			obj.loc = contact.movePoint(float(PI+angle_rotate), size + thickness);
		}
	}
}

void SpringPendulum::updateStateSpring()
{
	rotateSpring(-old_angle);
	ball.rotate(-Convert::RadiusToDegree(old_angle));

	contact = obj.loc.movePoint( float(angle_rotate),  ball.getRadius() + thickness);

	angle_rotate = (contact - anchor).angle() - float(PI / 2);
	float length_spring = (contact - anchor).mag();

	float unit_length_spring = length_spring / (texture_springs.size()-1);

	this->angle_spring = asinf(unit_length_spring / springs_width);

	this->updateSpringsAngle1(angle_spring);

	rotateSpring(angle_rotate);
	ball.rotate(Convert::RadiusToDegree(angle_rotate));
}


void SpringPendulum::drawSprings(sf::RenderWindow& window)
{
	for (auto& i : texture_springs) {
		window.draw(i);
	}
}

void SpringPendulum::reset()
{
	obj.acc.reset();
	obj.vec.reset();
	this->a_angle_rotate = 0.f;
	this->v_angle_rotate = 0.f;
}



