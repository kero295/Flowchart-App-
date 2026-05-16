#include "AddWrite.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddWrite::AddWrite(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddWrite::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();



	//Read the (Position) parameter
	pOut->PrintMessage("Write Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();


	pOut->PrintMessage("Please enter the variable name a value");
	variableOrValue = pIn->GetVariableOrValue(pOut);

	if (IsDrawnOnUI(Position) == true)
	{
		pOut->PrintMessage("Error: can't draw on the UI");
		return;
	}

}

bool AddWrite::IsDrawnOnUI(Point P)
{
	if ((P.y <= UI.ToolBarHeight) || ((P.x + UI.READWRITE_WIDTH / 2) >= UI.DrawingAreaWidth) || ((P.y + UI.READWRITE_HEIGHT) >= UI.height - UI.StatusBarHeight) || ((P.x - UI.READWRITE_WIDTH / 2) <= 0))
	{
		return true;
	}
}

void AddWrite::Execute()
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
	Corner.x = Position.x - UI.READWRITE_WIDTH / 2;
	Corner.y = Position.y;

	Write* pWrite = new Write(Corner, variableOrValue);


	pManager->AddStatement(pWrite); // Adds the created statement to application manger's statement list
}
