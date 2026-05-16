#include "AddVariableAssign.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddVarAssign::AddVarAssign(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

bool AddVarAssign::IsDrawnOnUI(Point P)
{
	if ((P.y <= UI.ToolBarHeight) || ((P.x + UI.ASSGN_WDTH / 2) >= UI.DrawingAreaWidth) || ((P.y + UI.ASSGN_HI) >= UI.height - UI.StatusBarHeight) || ((P.x - UI.ASSGN_WDTH / 2) <= 0))
	{
		return true;
	}
}

void AddVarAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();



	//Read the (Position) parameter
	pOut->PrintMessage("variable Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	pOut->PrintMessage("Please enter the variable name");
	leftvar = pIn->GetVariable(pOut);

	pOut->PrintMessage("Please enter the variable");
	rightvar = pIn->GetVariable(pOut);

	if (IsDrawnOnUI(Position) == true)
	{
		pOut->PrintMessage("Error: can't draw on the UI");
		return;
	}

}

void AddVarAssign::Execute()
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

	//Calculating left corner 
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	VarAssign* pAssign = new VarAssign(Corner, leftvar, rightvar);


	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

