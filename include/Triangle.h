#pragma once
#include "Vertex.h"
#include "Board.h"
#include "Rectangle.h"
#include "macros.h"

class ​Triangle {
public:
	​Triangle(const Vertex vertices[]);
	​Triangle(const Vertex& v0, const Vertex& v1, double height);
	Vertex getVertex(int index)const;
	double getHeight()const;
	double getLength()const;
	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;
	double getArea() const;
	double getPerimeter() const;
	Vertex getCenter() const;
	bool scale(double factor);
private:
	Vertex m_vertices[3];
	void triangleDefault();
};