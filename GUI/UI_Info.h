#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\DEFS.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)
	
	int width, height;	//Window width and height
	int wx, wy;			//Window starting coordinates

	int StatusBarHeight;	//Status Bar Width
	int ToolBarHeight;		//Tool Bar Width
	int MenuItemWidth;		//Menu Item Width
	int DrawingAreaWidth;   //Drawing Area Width
	
	color DrawColor;		//Drawing color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color DrawAreaColor;	//Draw area color

	int ASSGN_WDTH;		//Assignment statement default width
	int ASSGN_HI;		//Assignment statement default height

	int CONDITIONAL_VERTICAL_DIAGONAL;		//Conditional statement default vertical diagonal
	int CONDITIONAL_HORIZONTAL_DIAGONAL;	//Conditional statement default horizontal diagonal

	int READWRITE_WIDTH;	//Read & Write statement default width
	int READWRITE_HEIGHT;	//Read & Write statement default height
	int READWRITE_OFFSET;   //the offset that makes the parallelogram shape

	int STARTEND_HORIZONTAL_DIAMETER;  //Start & End statement default horizontal diameter
	int STARTEND_VERTICAL_DIAMETER;	 //Start & End statement default vertical diameter
	
}UI;	//create a single global object UI

struct Point	
{
	int x,y;
	Point(int a=0, int b=0)	//constructor
	{ x=a;	y=b;	}
};

#endif