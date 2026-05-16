#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1194;
	UI.height = 1000;
	UI.wx = 15;
	UI.wy =15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 100;
	UI.MenuItemWidth = 118;
	UI.DrawingAreaWidth = 0.75 * UI.width;

	UI.DrawColor = BLUE;
	UI.HighlightColor = RED;
	UI.MsgColor = DARKGREEN;
	UI.DrawAreaColor = { 255, 228, 196 };

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;

	UI.CONDITIONAL_VERTICAL_DIAGONAL = 100;
	UI.CONDITIONAL_HORIZONTAL_DIAGONAL = 100;

	UI.READWRITE_WIDTH = 120;
	UI.READWRITE_HEIGHT = 60;
	UI.READWRITE_OFFSET = UI.READWRITE_WIDTH / 4;

	UI.STARTEND_HORIZONTAL_DIAMETER = 100;
	UI.STARTEND_VERTICAL_DIAMETER = 55;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");
	
	pWind->SetPen(RED,3);


	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
	ClearOutputBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateDesignToolBar() //Draws the Design Menu
{
	UI.ToolBarHeight = 100;
	UI.AppMode = DESIGN;	//Design Mode
	
	//fill the tool bar 
		
	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in Defs.h ==> enum DrawMenuItem
	string MenuItemImages[DSN_ITM_CNT];

	//TODO: Prepare images for each menu item and add it to the list

	MenuItemImages[ITM_START] = "images\\start.jpg";
	MenuItemImages[ITM_END] = "images\\end.jpg";

	MenuItemImages[ITM_DECLARE_VARIABLE] = "images\\Declare.jpg";
	MenuItemImages[ITM_VALUE_ASSIGN] = "images\\Value Assign.jpg";
	MenuItemImages[ITM_VAR_ASSIGN] = "images\\Variable Assign.jpg";
	MenuItemImages[ITM_OPER_ASSIGN] = "images\\OP Assign.jpg";

	MenuItemImages[ITM_COND] = "images\\condition.jpg";

	MenuItemImages[ITM_CONNECTOR] = "images\\arrow.jpg";

	MenuItemImages[ITM_READ] = "images\\read.jpg";
	MenuItemImages[ITM_WRITE] = "images\\write.jpg";

	MenuItemImages[ITM_SELECT] = "images\\select.jpg";

	MenuItemImages[ITM_EDIT] = "images\\edit.jpg";
	MenuItemImages[ITM_DELETE] = "images\\delete.jpg";
	MenuItemImages[ITM_COPY] = "images\\copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\cut.jpg";
	MenuItemImages[ITM_PASTE] = "images\\paste.jpg";

	MenuItemImages[ITM_SAVE] = "images\\save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\load.jpg";

	MenuItemImages[ITM_SIM_MODE] = "images\\switch.jpg";

	MenuItemImages[ITM_EXIT] = "images\\exit.jpg";

	//Draw menu item one image at a time
	int i = 0;

	for ( i; i < DSN_ITM_CNT / 2; i++)
	{
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight / 2);
	}

	while (i < DSN_ITM_CNT)
	{
		pWind->DrawImage(MenuItemImages[i], (i - DSN_ITM_CNT / 2) * UI.MenuItemWidth, UI.ToolBarHeight / 2, UI.MenuItemWidth, UI.ToolBarHeight / 2 - 1);
		i++;
	}

	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	
}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateSimulationToolBar() //Draws the Simulation Menu
{
	ClearDSNToolBar();
	UI.ToolBarHeight = 50;
	ClearDrawArea();
	ClearOutputBar();
	UI.AppMode = SIMULATION;	//Simulation Mode
	///TODO: add code to create the simulation tool bar

	string MenuItemImages[SIM_ITM_CNT];

	MenuItemImages[ITM_VALIDATE] = "images\\validate.jpg";
	MenuItemImages[ITM_RUN] = "images\\run.jpg";
	MenuItemImages[ITM_GENERATE_CODE] = "images\\generate.jpg";
	MenuItemImages[ITM_EXIT_IN_SIM_MODE] = "images\\exit.jpg";
	MenuItemImages[ITM_DSN_MODE] = "images\\switch.jpg";

	for (int i = 0; i < SIM_ITM_CNT; i++)
	{
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	//color Bisque = { 255, 228, 196 }; this is the color used for the draw area

	pWind->SetPen(RED, 2);
	pWind->SetBrush(UI.DrawAreaColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDSNToolBar()
{
	pWind->SetPen(WHITE, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int) (UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Statements Drawing Functions							//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point topLeft, int width, int height, string Text, bool Selected)
{
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor,3);	//use normal color


	//Draw the statement block rectangle
	pWind->DrawRectangle(topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + height);
		
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(topLeft.x + width / 4, topLeft.y + height / 4, Text);
}

//TODO: Add similar functions for drawing all other statements.
//		e.g. DrawDeclareStat(.....), DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
//		Decide the parameters that should be passed to each of them

void Output::DrawStart(Point topLeft, int horizontalDiameter, int verticalDiameter, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color



	//Draw the statement block oval
	pWind->DrawEllipse(topLeft.x, topLeft.y, topLeft.x + horizontalDiameter, topLeft.y + verticalDiameter);

	//Write "Start" text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(topLeft.x + horizontalDiameter / 4, topLeft.y + verticalDiameter / 4, "Start");
}

void Output::DrawEnd(Point topLeft, int horizontalDiameter, int verticalDiameter, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color



	//Draw the statement block oval
	pWind->DrawEllipse(topLeft.x, topLeft.y, topLeft.x + horizontalDiameter, topLeft.y + verticalDiameter);

	//Write "End" text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(topLeft.x + horizontalDiameter / 4, topLeft.y + verticalDiameter / 4, "End");
}

void Output::DrawConditional(Point Top, int VerticalDiagonal, int HorizontalDiagonal, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color



	//Draw the Conditional statement (rhombus shaped)

	//Point Conditional[4] = { {Top.x, Top.y}, {Top.x, Top.y + VerticalDiagonal},  used it to get the points
	//	{Top.x + HorizontalDiagonal / 2, Top.y + VerticalDiagonal / 2},			   in an organized way before 
	//	{Top.x - HorizontalDiagonal / 2, Top.y + VerticalDiagonal / 2} };		   putting them in the array

	int X[4] = { Top.x , Top.x + HorizontalDiagonal / 2, Top.x  , Top.x - HorizontalDiagonal / 2 };
	
	int Y[4] = { Top.y , Top.y + VerticalDiagonal / 2, Top.y + VerticalDiagonal , Top.y + VerticalDiagonal / 2 };

	pWind->DrawPolygon(X, Y, 4);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Top.x - HorizontalDiagonal / 5 , Top.y + VerticalDiagonal / 2.5, Text);
}

void Output::DrawRead(Point topLeft, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color



	//Draw the Read statement (Parallelogram shaped)
	int offset = width / 4;

	int X[4] = { topLeft.x + width, topLeft.x, topLeft.x - offset, topLeft.x - offset + width };
	
	int Y[4] = { topLeft.y, topLeft.y, topLeft.y + height, topLeft.y + height };

	pWind->DrawPolygon(X, Y, 4);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(topLeft.x + width / 8, topLeft.y + height / 3, Text);
}

void Output::DrawWrite(Point topLeft, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color



	//Draw the Write statement (Parallelogram shaped)
	//int offset = width / 4;

	int X[4] = { topLeft.x + width, topLeft.x, topLeft.x - UI.READWRITE_OFFSET, topLeft.x - UI.READWRITE_OFFSET + width };

	int Y[4] = { topLeft.y, topLeft.y, topLeft.y + height, topLeft.y + height };

	pWind->DrawPolygon(X, Y, 4);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(topLeft.x + width / 8, topLeft.y + height / 3, Text);
}
	
//TODO: Add DrawConnector function

void Output::DrawConnector(Point start, Point end, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	if (end.y > start.y)	// normal connector
	{
		Point branchingConnector[3] = { {start.x, start.y}, {end.x, start.y}, {end.x, end.y} };

		if (end.x >= start.x)	// right side
		{
			pWind->DrawLine(branchingConnector[0].x, branchingConnector[0].y, branchingConnector[1].x, branchingConnector[1].y);
			pWind->DrawLine(branchingConnector[1].x, branchingConnector[1].y, branchingConnector[2].x, branchingConnector[2].y);

			int offset = 20;

			int Yoffset = end.y - offset;

			int Xoffset = 10;

			pWind->DrawTriangle(end.x, end.y, end.x + Xoffset, Yoffset, end.x - Xoffset, Yoffset);
		}
		else if (start.x > end.x)	// left side
		{
			branchingConnector[1].x = end.x;  branchingConnector[2].x = end.x;

			pWind->DrawLine(branchingConnector[0].x, branchingConnector[0].y, branchingConnector[1].x, branchingConnector[1].y);
			pWind->DrawLine(branchingConnector[1].x, branchingConnector[1].y, branchingConnector[2].x, branchingConnector[2].y);

			int offset = 20;

			int Yoffset = end.y - offset;

			int Xoffset = 10;

			pWind->DrawTriangle(end.x, end.y, end.x + Xoffset, Yoffset, end.x - Xoffset, Yoffset);
		}
	}
	else if (start.y > end.y)	// connector for doing loops with conditionals
	{
		Point conditionalConnector[4] = { {start.x, start.y}, {end.x + UI.ASSGN_WDTH / 2, start.y},
			{end.x + UI.ASSGN_WDTH / 2, end.y}, {end.x, end.y} };

		if (end.x >= start.x)	// right side
		{
			pWind->DrawLine(conditionalConnector[0].x, conditionalConnector[0].y, conditionalConnector[1].x, conditionalConnector[1].y);
			pWind->DrawLine(conditionalConnector[1].x, conditionalConnector[1].y, conditionalConnector[2].x, conditionalConnector[2].y);
			pWind->DrawLine(conditionalConnector[2].x, conditionalConnector[2].y, conditionalConnector[3].x, conditionalConnector[3].y);

			int offset = 28;

			int Xoffset = end.x + offset;

			int Yoffset = 10;

			pWind->DrawTriangle(end.x, end.y, Xoffset, end.y + Yoffset, Xoffset, end.y - Yoffset);
		}
		else if (start.x > end.x)	// left side
		{
			conditionalConnector[1].x = start.x + UI.ASSGN_WDTH / 2 ;  conditionalConnector[2].x = start.x + UI.ASSGN_WDTH / 2 ;

			pWind->DrawLine(conditionalConnector[0].x, conditionalConnector[0].y, conditionalConnector[1].x, conditionalConnector[1].y);
			pWind->DrawLine(conditionalConnector[1].x, conditionalConnector[1].y, conditionalConnector[2].x, conditionalConnector[2].y);
			pWind->DrawLine(conditionalConnector[2].x, conditionalConnector[2].y, conditionalConnector[3].x, conditionalConnector[3].y);

			int offset = 28;

			int Xoffset = end.x + offset;

			int Yoffset = 10;

			pWind->DrawTriangle(end.x, end.y, Xoffset + 4, end.y + Yoffset, Xoffset + 4, end.y - Yoffset);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}
