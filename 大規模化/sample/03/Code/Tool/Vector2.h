#pragma once
#include<cmath>

template<class T>
class Vector2 {
public:
	Vector2() :
		x((T)0),
		y((T)0)
	{}
	Vector2(T x, T y) :
		x(x),
		y(y)
	{}
	T x, y;

	const T &operator[] (const int &o) const {
		if (o == 0) {
			return x;
		}
		else if (o == 1) {
			return y;
		}
		else {
			throw "out of range at Vector2::operator()";
			return x;
		}
	}
	const Vector2 &operator() (const T &x, const T &y) {
		this->x = x;
		this->y = y;
		return (*this);
	}

	Vector2 operator+ (const Vector2 &o) const {
		return Vector2(x + o.x, y + o.y);
	}
	Vector2 operator- (const Vector2 &o) const {
		return Vector2(x - o.x, y - o.y);
	}
	const Vector2 &operator+= (const Vector2 &o) {
		(*this) = (*this) + o;
		return (*this);
	}
	const Vector2 &operator-= (const Vector2 &o) {
		(*this) = (*this) - o;
		return (*this);
	}
	const Vector2 &operator++ () {
		x++;
		y++;
		return (*this);
	}
	const Vector2 &operator-- () {
		x--;
		y--;
		return (*this);
	}

	Vector2 operator* (const T &o) const {
		return Vector2(x * o, y * o);
	}
	Vector2 operator/ (const T &o) const {
		if (o != 0) {
			return Vector2(x / o, y / o);
		}
		else {
			//throw "Vector2::operator/ div 0";
			return Vector2();
		}
	}
	const Vector2 &operator*= (const T &o) {
		(*this) = (*this) * o;
		return (*this);
	}
	const Vector2 &operator/= (const T &o) {
		(*this) = (*this) / o;
		return (*this);
	}

	T operator* (const Vector2 &o) const {
		return (x*o.x + y * o.y);
	} //ì‡êœ
	T crossProduct(const Vector2 &o) const {
		return (x*o.y - y * o.x);
	} //äOêœ

	T length2() const {
		return (x*x + y * y);
	}
	T length() const {
		return (T)sqrt((double)(length2()));
	}
	const Vector2 &normalize() {
		return (*this) /= length();
	}
	Vector2 getNormalized() const {
		return (*this) / length();
	}
	T getCos() const {
		return (x / length());
	}
	T getCos(const Vector2 &v) const {
		return (*this) * v / (T)sqrt((double)(length2() * v.length2()));
	}
	T getSin() const {
		return (y / length());
	}
	T getSin(const Vector2 &v) const {
		return (crossProduct(v) / (T)sqrt((double)(length2() * v.length2())));
	}

};

template<class T>
inline Vector2<T> operator* (const T &t, const Vector2<T> &o) {
	return (o * t);
}
template<class T>
inline Vector2<T> operator/ (const T &t, const Vector2<T> &o) {
	return (o / t);
}
