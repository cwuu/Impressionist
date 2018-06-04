#include<cmath>
#include<cassert>
#include "ScatteredLineBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name ) :ImpBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target)
{
	//not sure if this two lines are necessary- todo testing
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	assert(pDoc != NULL);
	int length = pDoc->getSize();

	int LX = target.x - length / 2.0;
	int	RX = target.x + length / 2.0;
	int	Y = target.y - length / 2.0;

	for (int i = 0; i < length ; ++i)
	{
		// simulate hash_func to give random x,y offset
		int offset_x = rand() % (length) - length;
		int offset_y = rand() % (length) - length;
		//GL_LINES need to be aware of the scope
		glBegin(GL_LINES);
		Point DrawPoint = Point(target.x + offset_x, target.y + offset_y);
		SetColor(DrawPoint);
		glVertex2f(RX + offset_x, Y + offset_y);
		glVertex2f(LX + offset_x, Y + offset_y);
		glEnd();

	}
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
}

