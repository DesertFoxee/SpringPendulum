#include "Vector2D.h"



Vector2D::Vector2D() {
	this->x = 0;
	this->y = 0;
}

Vector2D::Vector2D(const float & x, const float & y) 
	:x(x) , y(y)
{
	
}


Vector2D::Vector2D(const Vector2D & v) {
	this->x = v.x;
	this->y = v.y;
}

Vector2D::Vector2D(const sf::Vector2f & v) {
	this->x = v.x;
	this->y = v.y;
}


Vector2D & Vector2D::operator*=(const float & factor) {
	this->x *= float(factor);
	this->y *= float(factor);
	return *this;
}

Vector2D & Vector2D::operator/=(const float& factor) {
	if(factor) {
		this->x /= factor;
		this->y /= factor;
	};
	return *this;
}
Vector2D& Vector2D::operator+=(const Vector2D& v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2D::~Vector2D() {
	this->x = 0;
	this->y = 0;
}

Vector2D & Vector2D::operator=(const Vector2D & v) {
	this->x = v.x ;
	this->y = v.y;
	return *this;
}

Vector2D Vector2D::operator+(const Vector2D & v) const{
	return Vector2D(this->x+v.x , this->y+v.y);
}

Vector2D Vector2D::operator-(const Vector2D & v) const {
	return Vector2D(this->x - v.x, this->y - v.y);
}

Vector2D Vector2D::operator*(const float & factor) const{
	return Vector2D(this->x *factor , this->y*factor);
}

Vector2D Vector2D::operator/(const float & factor) const {
	if(factor) {
		return Vector2D(this->x /factor, this->y/factor);
	}
	return *this;
}

bool Vector2D::operator==(const Vector2D & v) const{
	return (this->x == v.x)&&(this->y == v.y);
}

bool Vector2D::operator!=(const Vector2D & v) const{
	return (this->x != v.x)||(this->y != v.y);
}

bool Vector2D::operator!=(const sf::Vector2f & v) const{
	return (this->x != v.x) || (this->y != v.y);
}

bool Vector2D::operator==(const sf::Vector2f & v) const{
	return (this->x == v.x) && (this->y == v.y);
}

sf::Vector2f Vector2D::toVec2f() const{
	return sf::Vector2f(this->x, this->y);
}



Vector2D & Vector2D::operator-=(const Vector2D & v) {
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

float Vector2D::mag() const {
	return std::sqrtf(this->x*this->x + this->y * this->y);
}

float Vector2D::mag(const Vector2D & v) const{
	Vector2D temp = *this - v;
	return temp.mag();
}

Vector2D Vector2D::normalize() const{
	float mag = this->mag();

	if(mag) {
		return Vector2D(this->x / mag, this->y / mag);
	}
	return Vector2D(0, 0);
}

void Vector2D::reset() {
	this->x = 0;
	this->y = 0;
}

float Vector2D::angle() const{
	return atan2f(this->y, this->x);
}

float Vector2D::angle(const Vector2D& v) const
{
	float scalar = this->x * v.x + this->y * v.y;
	float length = this->mag() * v.mag();
	return (length != 0) ? acosf(scalar / length) : 0.f;
}

void Vector2D::random(float min , float max) {
#ifdef RANDOM_H
	this->x = Random::randomFloatUniform(min, max);
	this->y = Random::randomFloatUniform(min, max);
#else
	this->x = 0; this->y = 0;
#endif // RANDOM_H

}

Vector2D Vector2D::rotate(float angle) const
{
	Vector2D v_result;
	v_result.x = cosf(angle) * x - sinf(angle) * y;
	v_result.y = sinf(angle) * x + cos(angle) * y;
	return v_result;
}

Vector2D Vector2D::movePoint(float angle, float distance) const
{
	Vector2D point_move;
	point_move.x = this->x + cosf(angle) * distance;
	point_move.y = this->y + sinf(angle) * distance;
	return point_move;
}
