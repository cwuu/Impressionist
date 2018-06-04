#ifndef CURVEBRUSH_H
#define CURVEBRUSH_H

#include "ImpBrush.h"

class CurveBrush : public ImpBrush
{
public:
	CurveBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);

	// Return the name of the brush .
	char* BrushName(void);
private:
	Point prePoint;
};

#endif
