#pragma once

// Una clase sencillita para manejar coordenadas X e Y juntas
class Vector2 {
public:
	int x;
	int y;

    // Constructores básicos
	Vector2()
		: x(0), y(0){}
	Vector2(int _x, int _y)
		: x(_x), y(_y) {}

    // Sumar dos vectores fácil con el símbolo 'mas' (posición + dirección)
	inline Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

    // Comprobar si dos posiciones son exactamente la misma
	inline bool operator==(const Vector2& other) const {
		return x == other.x && y == other.y;
	}

    // Invertir la dirección de golpe si uso una exclamación (aunque al final no lo uso mucho)
	inline void operator!() {
		x = -x;
		y = -y;
	}
};