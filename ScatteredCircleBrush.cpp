#include<cmath>
#include <cassert>
#include "ScatteredCircleBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name ) :ImpBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	//not sure if this two lines are necessary- todo testing
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
	
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	assert(pDoc != NULL);
	int size = pDoc->getSize();

	float radius = 6.0f;
	for (int i = 0; i <= (size*M_PI); ++i)
	{
		// simulate hash_func to give random x,y offset
		int offset_x = rand() % size - 1;
		int offset_y = rand() % size - 1;
		Point DrawPoint = Point(target.x + offset_x, target.y + offset_y);
		SetColor(DrawPoint);
		DrawFilledCircle(DrawPoint.x, DrawPoint.y, radius);
	}
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
}

void ScatteredCircleBrush::DrawFilledCircle(float x, float y, float radius)
{
	/*
	x (GLfloat) - the x position of the center point of the circle
	y (GLfloat) - the y position of the center point of the circle
	radius (GLfloat) - the radius that the painted circle will have
	*/
	
	int triangleAmount = 20;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= triangleAmount; ++i)
	{
		glVertex2f(x + (radius*cos(i*M_PI*2.0f / triangleAmount)), y + (radius*sin(i*M_PI*2.0f / triangleAmount)));
	}
	glEnd();
	
}