#include<cmath>
#include<cassert>
#include "LineBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name):ImpBrush(pDoc,name)
{
}
void LineBrush::BrushBegin(const Point source, const Point target)
{
	
	//not sure if this two lines are necessary- todo testing
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	
	prePoint = Point(target);

	BrushMove(source, target);
}
void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	assert(pDoc != NULL);
	int length = pDoc->getSize();
	int width = pDoc->getWidth();

	glLineWidth(width);

	//4 cases, wait for stroke type, switch 

	/* case1 --> break
	normal case (value slider)

	int LX = target.x - length / 2.0;
	int RX = target.x + length / 2.0;
	int	Y = target.y - length / 2.0;
	*/


	/*case2 --> drag direction line 
	*/
	int X1 = prePoint.x;
	int X2 = target.x;
	int	Y1 = prePoint.y;
	int	Y2 = target.y ;
	glBegin(GL_LINES);
	Point DrawPoint = Point(target.x, target.y);
	SetColor(DrawPoint);
	glVertex2f(X1, Y1);
	glVertex2f(X2, Y2);


	glEnd();

	/*case 3 --> mouse direction

	double angle = (atan2((target.y - prePoint.y),(target.x - prePoint.x))/M_PI*180.0);
	printf("angle:%f\n", angle);
	glPushMatrix();
	glTranslatef(target.x, target.y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	int LX = 0 - length / 2.0;
	int RX = 0 + length / 2.0;
	int	Y = 0 - length / 2.0;
	
	glLineWidth(width);
	glBegin(GL_LINES);
	Point DrawPoint = Point(target.x, target.y);
	SetColor(DrawPoint);
	glVertex2f(LX, Y );
	glVertex2f(RX, Y );
	

	glEnd();
	glPopMatrix();
		*/
	/*case 4 --> gradient


	double angle = pDoc->getGradientAngle(target.x,target.y)+90;
	glPushMatrix();
	glTranslatef(target.x, target.y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	int LX = 0 - length / 2.0;
	int RX = 0 + length / 2.0;
	int	Y = 0 - length / 2.0;

	glLineWidth(width);
	glBegin(GL_LINES);
	Point DrawPoint = Point(target.x, target.y);
	SetColor(DrawPoint);
	glVertex2f(LX, Y);
	glVertex2f(RX, Y);


	glEnd();
	glPopMatrix();
	*/
	prePoint = Point(target);

}


void LineBrush::BrushEnd(const Point source, const Point target)
{
}
