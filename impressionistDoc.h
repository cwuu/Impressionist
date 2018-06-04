// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"
#include "LineBrush.h"
#include "ScatteredLineBrush.h"
#include "ScatteredCircleBrush.h"
#include "ScatteredPointBrush.h"
#include "RingBrush.h"
class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image
	
	int		undo();							//called by UI to undo brush

	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType
	void	setStrokeDirection(int type);
	int		getSize();						// get the UI size
	void	setSize(int size);				// set the UI size
	int     getWidth();
	void	setWidth(int width);
	int		getAngle();
	void	setAngle(int angle);

	double	getColorR();
	double	 getColorG();
	double	 getColorB();
	void		setColor(double r, double g, double b);

	double		getAlpha();
	void	setAlpha(double alpha);
	char*	getImageName();					// get the current image name
	
	int		getGreyscale(int x, int y);

	int		SobelEdgeDetectionX(int intensity[9]);
	int		SobelEdgeDetectionY(int intensity[9]);
	double		getGradientAngle(int x, int y);

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;
	//bitmaps for the saved undo painting 
	unsigned char*	m_ucPaintingUndo;

	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	
	// Size of the brush.
	int m_nSize;							

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  


private:
	char			m_imageName[256];

};

extern void s(char *message);

#endif
