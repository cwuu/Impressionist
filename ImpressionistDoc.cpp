// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <cmath>
#include <iostream>
#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "LineBrush.h"
#include "ScatteredCircleBrush.h"
#include "CurveBrush.h"
#include "RingBrush.h"
#include "ScatteredLineBrush.h"

#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc()
{
	// Set NULL image name as init. 
	m_imageName[0] = '\0';

	m_nWidth = -1;
	m_ucBitmap = NULL;
	m_ucPainting = NULL;
	m_ucPaintingUndo = NULL;
	glEnable(GL_BLEND);
	// create one instance of each brush
	ImpBrush::c_nBrushCount = NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes = new ImpBrush*[ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS] = new PointBrush(this, "Points");

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]
		= new LineBrush(this, "Lines");
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]
		= new PointBrush(this, "Circles");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]
		= new ScatteredPointBrush(this, "Scattered Points");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]
		= new ScatteredLineBrush(this, "Scattered Lines");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]
		= new ScatteredCircleBrush(this, "Scattered Circles");
	ImpBrush::c_pBrushes[BRUSH_RINGS]
		= new RingBrush(this, "Rings");
	ImpBrush::c_pBrushes[BRUSH_CURVES]
		= new CurveBrush(this, "Curves");
	// make one of the brushes current
	m_pCurrentBrush = ImpBrush::c_pBrushes[0];

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui)
{
	m_pUI = ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName()
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush = ImpBrush::c_pBrushes[type];
}

void ImpressionistDoc::setStrokeDirection(int type)
{
	//m_pCurrentStroke = ImpBrush::c_pStroke[type];
	//TODO: change the stroke direction (for emily)
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------

double ImpressionistDoc::getColorR()
{
	return m_pUI->getColorR();
}
double ImpressionistDoc::getColorG()
{
	return m_pUI->getColorG();
}
double ImpressionistDoc::getColorB()
{
	return m_pUI->getColorB();
}

void ImpressionistDoc::setColor(double r, double g, double b)
{
	return m_pUI->setColor(r, g, b);
}
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

int ImpressionistDoc::getWidth()
{
	return m_pUI->getWidth();
}

int ImpressionistDoc::getAngle()
{
	return m_pUI->getAngle();
}

double ImpressionistDoc::getAlpha()
{
	return m_pUI->getAlpha() * 255;
}

void ImpressionistDoc::setSize(int size)
{
	m_pUI->setSize(size);
}

void ImpressionistDoc::setAngle(int angle)
{
	m_pUI->setAngle(angle);
}

void ImpressionistDoc::setWidth(int width)
{
	m_pUI->setWidth(width);
}

void ImpressionistDoc::setAlpha(double alpha)
{
	m_pUI->setAlpha(alpha);
}



//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname)
{
	// try to open the image to read
	unsigned char*	data;
	int				width,
		height;

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth = width;
	m_nPaintWidth = width;
	m_nHeight = height;
	m_nPaintHeight = height;

	// release old storage
	if (m_ucBitmap) delete[] m_ucBitmap;
	if (m_ucPainting) delete[] m_ucPainting;
	if (m_ucPaintingUndo) delete[]m_ucPaintingUndo;
	m_ucBitmap = data;

	// allocate space for draw view
	m_ucPainting = new unsigned char[width*height * 3];
	m_ucPaintingUndo = new unsigned char[width*height * 3];
	memset(m_ucPainting, 0, width*height * 3);
	memset(m_ucPaintingUndo, 0, width*height * 3);
	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(),
		m_pUI->m_mainWindow->y(),
		width * 2,
		height + 25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname)
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas()
{

	// Release old storage
	if (m_ucPainting)
	{
		delete[] m_ucPainting;

		// allocate space for draw view
		m_ucPainting = new unsigned char[m_nPaintWidth*m_nPaintHeight * 3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight * 3);
		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}

	return 0;
}

int ImpressionistDoc::undo()
{
	//TOBEDONE
	//for undo the last brush option 
	// allocate space for draw view
	unsigned char* m_tmp = m_ucPainting;
	m_ucPainting = m_ucPaintingUndo;
	m_ucPaintingUndo = m_tmp;
	m_pUI->m_paintView->refresh();
	glFlush();
	// refresh paint view as well		
	return 0;
}
//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel(int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= m_nWidth)
		x = m_nWidth - 1;

	if (y < 0)
		y = 0;
	else if (y >= m_nHeight)
		y = m_nHeight - 1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel(const Point p)
{
	return GetOriginalPixel(p.x, p.y);
}

int ImpressionistDoc::getGreyscale(int x, int y)
{
	GLubyte rgb[3];
	memcpy(rgb, GetOriginalPixel(x, y), 3);
	return 0.299*rgb[0] + 0.587*rgb[1] + 0.144*rgb[2];
}

int ImpressionistDoc::SobelEdgeDetectionX(int intensity[9])
{
	//x
	// 1 2 1
	// 0 0 0
	// -1 -2 -1

	return -1 * intensity[0] + -2 * intensity[1] - 1 * intensity[2] + 0 * (intensity[3] + intensity[4] + intensity[5]) + 1 * intensity[6] + 2 * intensity[7] + 1 * intensity[8];
}
int ImpressionistDoc::SobelEdgeDetectionY(int intensity[9])
{
	//y
	// 1 0 -1
	// 2 0 -2
	// 1 0 -1
	return -1 * intensity[0] + 1 * intensity[2] - 2 * intensity[3] + 0 * (intensity[1] + intensity[4] + intensity[7]) + 2 * intensity[5] + -1 * intensity[6] + 1 * intensity[8];
}
double ImpressionistDoc::getGradientAngle(int x, int y)
{
	int intensity[9];
	int i = 0;
	for (int j = -1; j <= 1; j++)
		for (int k = -1; k <= 1; k++)
		{
			intensity[i] = getGreyscale(x + j, y + k);
			++i;
		}
	int gradientX = SobelEdgeDetectionX(intensity);
	int gradientY = SobelEdgeDetectionY(intensity);

	return atan2(gradientY, gradientX) / M_PI * 180;
}



