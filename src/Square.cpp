#include "Square.h"
#include "Utilities.h"

//this constructor function checks validation of given bottom left and top right vertices of a square,
//and constructs one. if not valid, default values will be entered.
Square::Square(const Vertex& bottomLeft, const Vertex& topRight) : m_bottomLeft(bottomLeft), m_topRight(topRight)
{
	if (!bottomLeft.isValid() || !topRight.isValid() ||
		!topRight.isHigherThan(bottomLeft) || !topRight.isToTheRightOf(bottomLeft)
		|| !doubleEqual(topRight.m_row - bottomLeft.m_row, topRight.m_col - bottomLeft.m_col)) {

		m_bottomLeft = Vertex(20, 10);
		m_topRight = Vertex(30, 20);
	}

}// this function gets bottom left vertex of a sqare and builds one by reuse of the previous constructor
Square::Square(const Vertex& start, double length) : Square(start, { start.m_col + length, start.m_row - length }) {}

Vertex Square::getBottomLeft() const
{
	return m_bottomLeft;
}


Vertex Square::getTopRight() const
{
	return m_topRight;
}

double Square::getLength() const
{
	return m_topRight.m_col - m_bottomLeft.m_col;
}

//this func gets a paremeter of type board, then uses func of claas board, 
//drawLine to draw a  square as output 
void Square::draw(Board& board) const
{
	auto topLeft = Vertex{ m_bottomLeft.m_col, m_topRight.m_row };// build vertex from class square members
	auto bottomRight = Vertex{ m_topRight.m_col, m_bottomLeft.m_row };
	board.drawLine(m_bottomLeft, topLeft);
	board.drawLine(topLeft, m_topRight);
	board.drawLine(m_topRight, bottomRight);
	board.drawLine(bottomRight, m_bottomLeft);
}

Rectangle Square::getBoundingRectangle() const
{
	return { m_bottomLeft, m_topRight };
}

double Square::getArea() const
{
	return getLength() * getLength();
}

double Square::getPerimeter() const
{
	return getLength() * 4;
}

Vertex Square::getCenter() const
{
	return { m_bottomLeft.m_col + getLength() / 2, m_topRight.m_row - getLength() / 2 };
}

// this function gets a double variable as a factor for changing the size of a square.
// the vertices of the new square vertices will be for each vetex : center - (abs(center(col) - vertex(col)), same for col.
// then checks validation, if valid it updates values of vertices and returns true.
bool Square::scale(double factor)
{
	if (factor <= 0)
		return false;
	auto center = getCenter();
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