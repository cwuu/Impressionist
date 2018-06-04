#include<cmath>
#include <cassert>
#include "RingBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

RingBrush::RingBrush(ImpressionistDoc* pDoc, char* name) :ImpBrush(pDoc, name)
{
}

void RingBrush::BrushBegin(const Point source, const Point target)
{
	//not sure if this two lines are necessary- todo testing
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);

}

void RingBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	assert(pDoc != NULL);
	int size = pDoc->getSize();

	float radius = 6.0f;
		Point DrawPoint = Point(target.x, target.y);
		SetColor(DrawPoint);
		DrawRing(DrawPoint.x, DrawPoint.y, radius);

}

void RingBrush::BrushEnd(const Point source, const Point target)
{
}



void RingBrush::DrawRing(float x, float y, float radius) {
	static const double inc = M_PI / 12;
	static const double max = 2 * M_PI;
	glBegin(GL_LINE_LOOP);
	for (double d = 0; d < max; d += inc) {
		glVertex2f(cos(d) * radius + x, sin(d) * radius + y);
	}
	glEnd();
}