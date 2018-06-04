//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"
#include<iostream>

// Static class member initializations
int			ImpBrush::c_nBrushCount = 0;
ImpBrush**	ImpBrush::c_pBrushes = NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc,
	char*				name) :
	m_pDoc(pDoc),
	m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------

void ImpBrush::SetColor(const Point source, int alpha)
{
	ImpressionistDoc* pDoc = GetDocument();


	GLubyte color[4];

	memcpy(color, pDoc->GetOriginalPixel(source), 3);
	// set different color 
	color[3] = alpha;

	double selectR = pDoc->getColorR();
	double selectG = pDoc->getColorG();
	double selectB = pDoc->getColorB();
	//	color[0] = (color[0]*0.3+ color[0]*selectR*0.7)/0.3;
	//color[1] = (color[1] * 0.3 + color[1]*selectG*0.7) / 0.3;
	//color[2] = (color[2] * 0.3 + color[1]*selectB*0.7) / 0.3;
	color[0] = int(color[0] * selectR);
	color[1] = int(color[1] * selectG);
	color[2] = int(color[2] * selectB);
	glColor4ubv(color);

}

void ImpBrush::SetColor(const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();
	SetColor(source, pDoc->getAlpha());
}