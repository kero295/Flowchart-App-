#include "AddEnd.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddEnd::AddEnd(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddEnd::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();



	//Read the (Position) parameter
	pOut->PrintMessage("End Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	if (IsDrawnOnUI(Position) == true)
	{
		pOut->PrintMessage("Error: can't draw on the UI");
		return;
	}
}

bool AddEnd::IsDrawnOnUI(Point P)
{
	if (((P.y <= UI.ToolBarHeight) || ((P.x + UI.STARTEND_HORIZONTAL_DIAMETER / 2) >= UI.DrawingAreaWidth) || ((P.y + UI.STARTEND_VERTICAL_DIAMETER) >= UI.height - UI.StatusBarHeight)) || ((P.x - UI.STARTEND_HORIZONTAL_DIAMETER / 2) <= 0))
	{
		return true;
	}
}

void AddEnd::Execute()
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
	Corner.x = Position.x - UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2;
	Corner.y = Position.y;

	End* pEnd = new End(Corner);

	pManager->AddStatement(pEnd);
}

