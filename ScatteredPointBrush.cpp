#include <cmath>
#include <cassert>
#include "ScatteredPointBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"



ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name):ImpBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target)
{
	//not sure if this two lines are necessary- todo testing
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	assert(pDoc != NULL);
	int size = pDoc->getSize();
	
	//M_PI influence computation?

	const float unitPoint = 1;
	glPointSize(unitPoint);

	for (int i = 0; i <= (size*M_PI) ; ++i)
	{ 
		// simulate hash_func to give random x,y offset
		int offset_x = rand() % size - 1;
		int offset_y = rand() % size - 1;
		glBegin(GL_POINTS);
		Point DrawPoint = Point(target.x + offset_x, target.y + offset_y);
		SetColor(DrawPoint);
		glVertex2d(DrawPoint.x, DrawPoint.y);
		glEnd();
	}
				
}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target)
{
}