#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "Random.h"

#include <SFML/Graphics.hpp>


class Vector2D {
	public:
		float x;
		float y;

	public:
		Vector2D();
		explicit Vector2D(const float& x, const float& y);
		Vector2D(const Vector2D& v);
		Vector2D(const sf::Vector2f& v);

		~Vector2D();
	
		Vector2D & operator=(const Vector2D& v);

		Vector2D&  operator+=(const Vector2D& v);
		Vector2D&  operator-=(const Vector2D& v);
		Vector2D&  operator*=(const float& factor);
		Vector2D&  operator/=(const float& factor);


		Vector2D  operator+(const Vector2D& v) const;
		Vector2D  operator-(const Vector2D& v) const ;
		Vector2D  operator*(const float& factor) const;
		Vector2D  operator/(const float& factor) const;


		bool operator==(const Vector2D& v) const;
		bool operator!=(const Vector2D& v) const;
		bool operator!=(const sf::Vector2f& v) const;
		bool operator==(const sf::Vector2f& v) const;

		sf::Vector2f toVec2f() const;


		float mag() const;
		float mag(const Vector2D &v) const;
		Vector2D normalize() const;
		float angle() const;
		float angle(const Vector2D &v) const;
		void random(float min, float max);
		Vector2D rotate(float angle) const ;

		Vector2D movePoint(float angle, float distance) const;

		void reset();
};

#endif // !VECTOR2D_H




