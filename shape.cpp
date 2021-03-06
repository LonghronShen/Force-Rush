#include "shape.h"
#include "system.h"
#include <cmath>

fr::Vector2Di::Vector2Di(int load_x, int load_y)
{
	x = load_x;
	y = load_y;
	length = sqrt(x * x + y * y);
	angle = atan(double(y) / double(x));
}

fr::Vector2Di::Vector2Di(double load_length, double load_angle)
{
	length = load_length;
	angle = load_angle;
	x = load_length * cos(load_angle);
	y = load_length * sin(load_angle);
}

fr::Vector2Di fr::Vector2Di::operator+(fr::Vector2Di input)
{
	return Vector2Di(x + input.x, y + input.y);
}

fr::Vector2Di fr::Vector2Di::operator-(fr::Vector2Di input)
{
	return Vector2Di(x - input.x, y - input.y);
}

fr::Vector2Di fr::Vector2Di::operator*(double input)
{
	return Vector2Di(int(x * input), int(y * input));
}

fr::Vector2Di fr::Vector2Di::operator/(double input)
{
	return Vector2Di(int(x / input), int(y / input));
}

int fr::Vector2Di::operator*(fr::Vector2Di input)
{
	return x * input.x + y * input.y;
}

double fr::Vector2Di::GetIntersectingAngle(Vector2Di input)
{
	int output = angle - input.angle;
	output = output > 0 ? output : -output;
	return output;
}

fr::Vector2Di fr::Point::operator-(Point input)
{
	return Vector2Di(x - input.x, y - input.y);
}

fr::Point fr::Point::operator+(fr::Vector2Di input)
{
	return Point(x + input.x, y + input.y);
}

void fr::Triangle::SetRotation(Point load_center, double load_angle)
{
	center = load_center;
	angle = load_angle;
	Vector2Di center2p1 = p1 - center;
	Vector2Di center2p2 = p2 - center;
	Vector2Di center2p3 = p3 - center;

	center2p1 = Vector2Di(center2p1.length, center2p1.angle + load_angle);
	center2p2 = Vector2Di(center2p2.length, center2p2.angle + load_angle);
	center2p3 = Vector2Di(center2p3.length, center2p2.angle + load_angle);
	//Rotation
	current_p1 = center + center2p1;
	current_p2 = center + center2p2;
	current_p3 = center + center2p3;
}

bool fr::Triangle::IsPointOnTriangle(Point input)
{
	Vector2Di point2p1 = current_p1 - input;
	Vector2Di point2p2 = current_p2 - input;
	Vector2Di point2p3 = current_p3 - input;
	int angle_sum = point2p1.GetIntersectingAngle(point2p2) + point2p2.GetIntersectingAngle(point2p3) + point2p3.GetIntersectingAngle(point2p1);
	return angle_sum == 180;
}

fr::Shape::Shape(std::initializer_list<fr::Triangle> load_triangle)
{
	for (auto i = load_triangle.begin(); i != load_triangle.end(); i++)
	{
		m_triangle.push_back(*i);
	}
}

bool fr::Shape::IsPointOnShape(Point input)
{
	bool output = false;
	for (int i = 0; i < m_triangle.size(); i++)
	{
		output = output ? true : m_triangle[i].IsPointOnTriangle(input);
	}
	return output;
}
