#include "AddOperatorAssign.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddOperatorAssign::AddOperatorAssign(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

bool AddOperatorAssign::IsDrawnOnUI(Point P)
{
	if ((P.y <= UI.ToolBarHeight) || ((P.x + UI.ASSGN_WDTH / 2) >= UI.DrawingAreaWidth) || ((P.y + UI.ASSGN_HI) >= UI.height - UI.StatusBarHeight) || ((P.x - UI.ASSGN_WDTH / 2) <= 0))
	{
		return true;
	}
}

void AddOperatorAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();



	//Read the (Position) parameter
	pOut->PrintMessage("Operator Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	pOut->PrintMessage("Please enter the variable name");
	Left_Var = pIn->GetVariable(pOut);

	pOut->PrintMessage("Please enter a variable or a value");
	Right_Var1 = pIn->GetVariableOrValue(pOut);

	pOut->PrintMessage("Please enter an operator");
	Right_Op = pIn->GetArithOperator(pOut);

	pOut->PrintMessage("Please enter a variable or a value");
	Right_Var2 = pIn->GetVariableOrValue(pOut);

	if (IsDrawnOnUI(Position) == true)
	{
		pOut->PrintMessage("Error: can't draw on the UI");
		return;
	}

}

void AddOperatorAssign::Execute()
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
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	OperatorAssign* pOperatorAssign = new OperatorAssign(Corner, Left_Var, Right_Var1, Right_Var2, Right_Op);


	pManager->AddStatement(pOperatorAssign); // Adds the created statement to application manger's statement list
}

