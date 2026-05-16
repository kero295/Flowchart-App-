#include "AddStart.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddStart::AddStart(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

bool AddStart::IsDrawnOnUI(Point P)
{
	if (((P.y <= UI.ToolBarHeight) || ((P.x + UI.STARTEND_HORIZONTAL_DIAMETER / 2) >= UI.DrawingAreaWidth) || ((P.y + UI.STARTEND_VERTICAL_DIAMETER) >= UI.height - UI.StatusBarHeight)) || ((P.x - UI.STARTEND_HORIZONTAL_DIAMETER / 2) <= 0))
	{
		return true;
	}
}

void AddStart::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();



	//Read the (Position) parameter
	pOut->PrintMessage("Start Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	if (IsDrawnOnUI(Position) == true)
	{
		pOut->PrintMessage("Error: can't draw on the UI");
		return;
	}
}

void AddStart::Execute()
{
	ReadActionParameters();

	if (IsDrawnOnUI(Position) == true)
	{
		return;
	}

	if (pManager->IsStatementOverlapping(Position) == true)
	{
		return;
	}

	Point Corner;
	Corner.x = Position.x - UI.STARTEND_HORIZONTAL_DIAMETER / 2;
	Corner.y = Position.y;

	Start* pStart = new Start(Corner);


	pManager->AddStatement(pStart); // Adds the created statement to application manger's statement list
}

