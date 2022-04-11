#include "Rectangle.h"


//this constructor function checks validation of given bottom left and top right vertices of a rectangle
//and constructs one. if not valid, default values will be entered by using rictangleDefault func.

Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight) :
	m_bottomLeft(bottomLeft), m_topRight(topRight)
{
	if (!bottomLeft.isValid() || !topRight.isValid() ||
		!topRight.isHigherThan(bottomLeft) || !topRight.isToTheRightOf(bottomLeft))
		rectangleDefault();

}// this constructor function gets an array of 2 vertices, uses the previous constructor to build a rectangle
Rectangle::Rectangle(const Vertex vertices[2]) : Rectangle(vertices[0], vertices[1]) {}

// this constructor function receives 4 doubles, uses previous constructor and struct Vertex to build a rectangle
Rectangle::Rectangle(double x0, double y0, double x1, double y1) : Rectangle({ x0, y0 }, { x1, y1 }) {}

// this constructor function receives a bttom left vertex of a rectangle, the width and the height ,and
// constructs a rectangle by reuse of a previous constructor.
Rectangle::Rectangle(const Vertex& start, double width, double height)
	: Rectangle(start, { start.m_col + width, start.m_row + height }) {}


Vertex Rectangle::getBottomLeft() const
{
	return m_bottomLeft;
}

Vertex Rectangle::getTopRight() const
{
	return m_topRight;
}

double Rectangle::getWidth() const
{
	return getTopRight().m_col - getBottomLeft().m_col;
}

void Rectangle::rectangleDefault()
{
	m_bottomLeft = Vertex(20, 10);
	m_topRight = Vertex(30, 20);
}

double Rectangle::getHeight() const
{
	return getTopRight().m_row - getBottomLeft().m_row;
}

//this func gets a paremeter of type board, then uses func of claas board, 
//drawLine to draw a  rectangle as output 
void Rectangle::draw(Board& board) const
{
	auto topLeft = Vertex{ m_bottomLeft.m_col, m_topRight.m_row }; // build vertex from class rectangle members
	auto bottomRight = Vertex{ m_topRight.m_col, m_bottomLeft.m_row };
	board.drawLine(m_bottomLeft, topLeft);
	board.drawLine(topLeft, m_topRight);
	board.drawLine(m_topRight, bottomRight);
	board.drawLine(bottomRight, m_bottomLeft);
}

Rectangle Rectangle::getBoundingRectangle() const
{
	return { *this };
}

double Rectangle::getArea() const
{
	return getWidth() * getHeight();
}

double Rectangle::getPerimeter() const
{
	return getWidth() * 2 + getHeight() * 2;
}

Vertex Rectangle::getCenter() const
{
	return { m_bottomLeft.m_col + getWidth() / 2,  m_bottomLeft.m_row + getHeight() / 2 };
}
// this function gets a double variable as a factor for changing the size of a rectangle.
// the vertices of the new triangle vertices will be for each vetex : center - (abs(center(col) - vertex(col)), same for col.
// then checks validation, if valid it updates values of vertices and returns true.

bool Rectangle::scale(double factor)
{
	if (factor <= 0)
		return false;
	auto center = getCenter();// center of the rectangle
	auto newBottomLeft = Vertex{ center.m_col - (center.m_col - m_bottomLeft.m_col) * factor,
						   center.m_row - (center.m_row - m_bottomLeft.m_row) * factor };
	auto newTopRight = Vertex{ center.m_col + (m_topRight.m_col - center.m_col) * factor,
						  center.m_row + (m_topRight.m_row - center.m_row) * factor };

	if (!newBottomLeft.isValid() || !newTopRight.isValid())
		return false;

	m_bottomLeft = newBottomLeft;// if valid
	m_topRight = newTopRight;
	return true;
}