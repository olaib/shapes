#include "Hourglass.h"
#include "Triangle.h"
#include "utilities.h"
#include <cmath>

//this constructor function checks validation of given 2 triangles upper and lower of a hourglass and constructs it
//if hourglass is not valid default values will be the values of the hourglass by using hourglassDefault func.
Hourglass::Hourglass(const ​Triangle& upper, const ​Triangle& lower) : m_upper(upper), m_lower(lower) {
	if (!doubleEqual(upper.getLength(), lower.getLength()) ||
		!sameCol(upper.getVertex(2), lower.getVertex(2)) ||
		!sameRow(upper.getVertex(2), lower.getVertex(2)) ||
		!upper.getVertex(0).isHigherThan(lower.getVertex(0)))
		hourglassDefault();
}

//this constructor function checks validation of a lower triangles of hourglass and 
//checks validation of upper triangle, if not so the hourglass will be updated to default values
Hourglass::Hourglass(const ​Triangle& lower) : Hourglass({ { lower.getVertex(0).m_col, lower.getVertex(0).m_row + 2 * lower.getHeight()} ,
					   { lower.getVertex(1).m_col, lower.getVertex(1).m_row + 2 * lower.getHeight() }, lower.getHeight() },
						 lower) {
	if (lower.getVertex(2).m_row + lower.getHeight() >= MAX_ROW)
		hourglassDefault();
}

double Hourglass::getLength() const
{
	return m_upper.getLength();
}

double Hourglass::getHeight() const
{
	return m_lower.getHeight() + abs(m_upper.getHeight());
}


//this func gets a paremeter of type board and then uses func of claas board, 
//drawLine to draw a hourglass as output 
void Hourglass::draw(Board& board) const
{
	m_lower.draw(board);
	m_upper.draw(board);
}

Rectangle Hourglass::getBoundingRectangle() const
{
	return { m_lower.getVertex(0),{ m_lower.getVertex(1).m_col,
			 m_lower.getVertex(1).m_row + 2 * m_lower.getHeight()} };
}

double Hourglass::getArea() const
{
	return m_lower.getArea() * 2;
}

double Hourglass::getPerimeter() const
{
	return m_lower.getPerimeter() * 2;
}

Vertex Hourglass::getCenter() const
{
	return  m_lower.getVertex(2);
}

// this function gets a factor(double type) for resizing the shape of a hourglass.
// the vertices of this triangle after resizing will be : center -or+ (abs(center(col) - m_lower.getVertex(col)), same for row.
// then checks validation, if not valid returns false.
bool Hourglass::scale(double factor)
{

	if (factor <= 0)
		return false;
	auto center =  m_lower.getCenter();
	Vertex scaledLTriangle[3] = { { center.m_col - (center.m_col - m_lower.getVertex(0).m_col) * factor,
								   center.m_row - (center.m_row - m_lower.getVertex(0).m_row) * factor},
								 { center.m_col + (m_lower.getVertex(1).m_col - center.m_col) * factor,
								   center.m_row - (center.m_row - m_lower.getVertex(1).m_row) * factor},
								   center  };

	if (!buildScaledTriangle(m_lower, scaledLTriangle))
		return false;


	Vertex scaledUTriangle[3] = { { center.m_col - (center.m_col - m_upper.getVertex(0).m_col) * factor,
						   center.m_row + (m_upper.getVertex(0).m_row - center.m_row) * factor},
						  {center.m_col + (m_upper.getVertex(1).m_col - center.m_col) * factor,
						   center.m_row + (m_upper.getVertex(1).m_row - center.m_row) * factor} ,
						   center };
	return buildScaledTriangle(m_upper, scaledUTriangle);

}

void Hourglass::hourglassDefault()
{
	Vertex lowerDefault[] = { {20, 20}, {30, 20}, {20, 20 + sqrt(75)} },
		upperDefault[] = { {30, 20 + 2 * sqrt(75)}, {20, 20 + 2 * sqrt(75)}, {25, 20 + sqrt(75)} };
	m_lower = { lowerDefault };
	m_upper = { upperDefault };
}

//this func checks validation of all the vertices of given triangle(upper or lower) and returns true if
//the triangle is valid if not so returns false 
bool Hourglass::buildScaledTriangle(​Triangle & triangle, Vertex scaledT[])
{
	
	for (size_t i = 0; i < 3; i++)
		if (scaledT[i].isValid())
			return false;

	for (size_t i = 0; i < 3; i++)
		 triangle.getVertex(i) = scaledT[i];
	return true;
}
