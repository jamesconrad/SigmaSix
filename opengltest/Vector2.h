#ifndef VEC2_H
#define VEC2_H
class vec2
{
public:
	vec2() { x = y = 0; }
	vec2(float _x, float _y) { x = _x; y = _y; }

	//Operators
	vec2 operator*(float _scale)
	{
		return vec2(x*_scale, y*_scale);
	}
	vec2 operator+(vec2 _b)
	{
		return vec2(x + _b.x, y + _b.y);
	}
	vec2 operator+=(vec2 _b)
	{
		x = x + _b.x;
		y = y + _b.y;
	}
	//Vars
	float x, y;
};
#endif