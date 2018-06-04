//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Color_Chooser.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;

	PaintView*			m_paintView;
	OriginalView*		m_origView;
	//for color dialog
	Fl_Window*			m_colorDialog;

	Fl_Color_Chooser*	m_ColorChooser;

	// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;
	Fl_Choice*			m_StrokeDirection;
	Fl_Slider*			m_BrushSizeSlider;
	//TODO: new added sliders
	Fl_Slider*			m_LineThicknessSlider;
	Fl_Slider*			m_BrushAngleSlider;
	Fl_Slider*			m_AlphaValueSlider;
	Fl_Slider*			m_EdgeThresholdSlider;
	Fl_Button*			m_DoItButton;
	Fl_Button*          m_ClearCanvasButton;
	//undo last operation button
	Fl_Button*			m_UndoCanvasButton;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	void				setSize(int size);
	//for thickness
	int					getWidth();
	void				setWidth(int width);
	//for angle
	int					getAngle();
	void				setAngle(int angle);

	// get the alpha value 
	double				getAlpha();
	void				setAlpha(double alpha);

	// get the RGB color
	double				getColorR();
	double				getColorG();
	double				getColorB();
	void				setColor(double r, double g, double b);

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

									// All attributes here
	int		m_nSize, m_nWidth, m_nAngle;
	double	m_nR, m_nG, m_nB;
	double				m_nAlpha;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE + 1];

	static Fl_Menu_Item		strokeDirectionMenu[3];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 

	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	//color dialog callback functions 
	static void cb_color(Fl_Menu_* o, void* v);
	static void cb_color_choose(Fl_Widget* o, void* v);
	//end color dialog
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void cb_undo_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	//TODO: new call back function for new sliders
	static void cb_strokeDirection(Fl_Widget* o, void* v);

	static void cb_widthSlides(Fl_Widget* o, void* v);
	static void cb_angleSlides(Fl_Widget* o, void* v);
	static void cb_alphaValue(Fl_Widget* o, void* v);
};

#endif
