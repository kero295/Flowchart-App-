#include "AddRead.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddRead::AddRead(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

bool AddRead::IsDrawnOnUI(Point P)
{
	if ((P.y <= UI.ToolBarHeight) || ((P.x + UI.READWRITE_WIDTH / 2) >= UI.DrawingAreaWidth) || ((P.y + UI.READWRITE_HEIGHT) >= UI.height - UI.StatusBarHeight) || ((P.x - UI.READWRITE_WIDTH / 2) <= 0))
	{
		return true;
	}
}

void AddRead::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();



	//Read the (Position) parameter
	pOut->PrintMessage("Read Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();


	pOut->PrintMessage("Please enter the variable name");
	variable = pIn->GetVariable(pOut);

	if (IsDrawnOnUI(Position) == true)
	{
		pOut->PrintMessage("Error: can't draw on the UI");
		return;
	}

}

void AddRead::Execute()
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

	Read* pRead = new Read(Corner, variable);


	pManager->AddStatement(pRead); // Adds the created statement to application manger's statement list
}
