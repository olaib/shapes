
#include <cmath>
#include "macros.h"
#include "vertex.h"
#include "Board.h"
#include "Triangle.h"
#include "Utilities.h"

//this constructor function checks validation of given three vertices of a triangle and constructs triangle
//if triangle is not valid default values will be the values of the triangle by using triangleDefault func.
​Triangle::​Triangle(const Vertex vertices[]) : m_vertices{ vertices[0], vertices[1], vertices[2] }
{
	if (!sameRow(vertices[0], vertices[1]) || !(doubleEqual(distance(vertices[0], vertices[1]), distance(vertices[1], vertices[2]))) ||
		!(doubleEqual(distance(vertices[1], vertices[2]), distance(vertices[0], vertices[2]))))
		triangleDefault();
}

void ​Triangle::triangleDefault() {
	m_vertices[0] = { 20,20 };
	m_vertices[1] = { 30, 20 };
	m_vertices[2] = { 25, 20 + sqrt(75) };
}

// this constructor function gets two vertices and height, returns void
​Triangle::​Triangle(const Vertex& v0, const Vertex& v1, double height) :
	m_vertices{ v0, v1, {(v0.m_col + v1.m_col) / 2, v0.m_row - height} } {}

Vertex ​Triangle::getVertex(int index) const
{
	return m_vertices[index];
}


double ​Triangle::getHeight() const
{
	return abs(getVertex(2).m_row - getVertex(1).m_row);
}

double ​Triangle::getLength() const
{
	return distance(getVertex(0), getVertex(1));
}

//this func gets a paremeter of type board and then uses func of claas board, 
//drawLine to draw a triangle as output 
void ​Triangle::draw(Board& board) const
{
	board.drawLine(m_vertices[0], m_vertices[1]);
	board.drawLine(m_vertices[0], m_vertices[2]);
	board.drawLine(m_vertices[1], m_vertices[2]);
}

Rectangle ​Triangle::getBoundingRectangle() const
{
	return { m_vertices[0], getLength(), getHeight() };
}

double ​Triangle::getArea() const
{
	return getLength() * getHeight() / 2;
}

double ​Triangle::getPerimeter() const
{
	return distance(m_vertices[0], m_vertices[1]) +
		distance(m_vertices[0], m_vertices[2]) +
		distance(m_vertices[1], m_vertices[2]);
}

Vertex ​Triangle::getCenter() const
{
	return Vertex(m_vertices[2].m_col, m_vertices[0].m_row + getHeight() / 2);
}

// this function gets a factor(double type) for resizing the shape of a triangle.
// the vertices of this triangle after resizing will be : center - (abs(center(col) - vertex(col)), same for row.
// then checks validation, if valid it updates values of vertices and returns true, else returns false.
bool ​Triangle::scale(double factor)
{
	if (factor <= 0)
		return false;
	auto center = getCenter();
	Vertex scaledTriangle[3] = { { center.m_col - (center.m_col - m_vertices[0].m_col) * factor,
								   center.m_row - (center.m_row - m_vertices[0].m_row) * factor},
								 { center.m_col + (m_vertices[1].m_col - center.m_col) * factor,
								   center.m_row - (center.m_row - m_vertices[1].m_row) * factor},
								 { center.m_col, center.m_row + (m_vertices[2].m_row - center.m_row) * factor} };
	for (size_t i = 0; i < 3; i++)
		if (!scaledTriangle[i].isValid())
			return false;

	for (size_t i = 0; i < 3; i++)
		m_vertices[i] = scaledTriangle[i];
		return true;
}

