#pragma once
#ifndef RINGBRUSH_H
#define RINGBRUSH_H

#include "ImpBrush.h"
class RingBrush : public ImpBrush
{
public:
	RingBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);

	// Return the name of the brush .
	char* BrushName(void);
private:
	//helper function
	void RingBrush::DrawRing(float x, float y, float radius);

};

#endif