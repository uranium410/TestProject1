#pragma once

class Vector2 {
public:
	int x;
	int y;
	Vector2() {};
	Vector2(int newX, int newY) { x = newX; y = newY; }

	/*演算子のオーバーロード*/
	Vector2 operator + (Vector2 another) {
		return Vector2(this->x + another.x, this->y + another.y);
	}

	Vector2 operator += (Vector2 another) {
		this->x = this->x + another.x;
		this->y = this->y + another.y;
		return *this;
	}

	Vector2 operator - (Vector2 another) {
		return Vector2(this->x + another.x, this->y + another.y);
	}

	Vector2 operator -= (Vector2 another) {
		this->x = this->x - another.x;
		this->y = this->y - another.y;
		return *this;
	}

	Vector2 operator / (Vector2 another) {
		return Vector2(this->x / another.x, this->y / another.y);
	}

	Vector2 operator /= (Vector2 another) {
		this->x = this->x / another.x;
		this->y = this->y / another.y;
		return *this;
	}


	Vector2 operator / (int another) {
		return Vector2(this->x / another, this->y / another);
	}

	Vector2 operator /= (int another) {
		this->x = this->x / another;
		this->y = this->y / another;
		return *this;
	}

	Vector2 operator * (int another) {
		return Vector2(this->x + another, this->y + another);
	}

	Vector2 operator *= (int another) {
		this->x = this->x * another;
		this->y = this->y * another;
		return *this;
	}

	bool operator == (Vector2 another) {
		if (this->x == another.x && this->y == another.y)return true;
		return false;
	}

	bool operator != (Vector2 another) {
		if (this->x == another.x && this->y == another.y)return false;
		return true;
	}
	
	int innerProduct(Vector2 another) {
		return this->x * another.y + this->y * another.x;
	}

	int crossProduct(Vector2 another) {
		return this->x * another.y - this->y * another.x;
	}

};

class Vector3 {
	int x;
	int y;
	int z;
	Vector3() {};
	Vector3(int newX, int newY, int newZ) { x = newX; y = newY; z = newZ; };
};

class DoubleVector2 {
public:
	double x;
	double y;
	DoubleVector2(double newX = 0, double newY = 0) { x = newX; y = newY; }

	/*演算子のオーバーロード*/
	DoubleVector2 operator + (DoubleVector2 another) {
		return DoubleVector2(this->x + another.x, this->y + another.y);
	}

	DoubleVector2 operator += (DoubleVector2 another) {
		this->x = this->x + another.x;
		this->y = this->y + another.y;
		return *this;
	}
	
	DoubleVector2 operator - (DoubleVector2 another) {
		return DoubleVector2(this->x + another.x, this->y + another.y);
	}

	DoubleVector2 operator -= (DoubleVector2 another) {
		this->x = this->x - another.x;
		this->y = this->y - another.y;
		return *this;
	}

	DoubleVector2 operator / (DoubleVector2 another) {
		return DoubleVector2(this->x / another.x, this->y / another.y);
	}

	DoubleVector2 operator /= (DoubleVector2 another) {
		this->x = this->x / another.x;
		this->y = this->y / another.y;
		return *this;
	}


	DoubleVector2 operator / (double another) {
		return DoubleVector2(this->x / another, this->y / another);
	}

	DoubleVector2 operator /= (double another) {
		this->x = this->x / another;
		this->y = this->y / another;
		return *this;
	}

	DoubleVector2 operator * (double another) {
		return DoubleVector2(this->x + another, this->y + another);
	}

	DoubleVector2 operator *= (double another) {
		this->x = this->x * another;
		this->y = this->y * another;
		return *this;
	}

	bool operator == (DoubleVector2 another) {
		if (this->x == another.x && this->y == another.y)return true;
		return false;
	}

	bool operator != (DoubleVector2 another) {
		if (this->x == another.x && this->y == another.y)return false;
		return true;
	}

	double innerProduct(DoubleVector2 another) {
		return this->x * another.y + this->y * another.x;
	}

	double crossProduct(DoubleVector2 another) {
		return this->x * another.y - this->y * another.x;
	}

	double articleLength() {
		return this->x * this->x + this->y * this->y;
	}

};