#include "AddConditional.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddConditional::AddConditional(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddConditional::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();



	//Read the (Position) parameter
	pOut->PrintMessage("Conditional Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();


	pOut->PrintMessage("Please enter the left hand side");
	LHS = pIn->GetVariableOrValue(pOut);


	pOut->PrintMessage("Please enter the comparison operator");
	ComparisonOperator = pIn->GetCompOperator(pOut);

	pOut->PrintMessage("Please enter the right hand side");
	RHS = pIn->GetVariableOrValue(pOut);

	if (IsDrawnOnUI(Position) == true)
	{
		pOut->PrintMessage("Error: can't draw on the UI");
		return;
	}

}

bool AddConditional::IsDrawnOnUI(Point P)
{
	if ((P.y <= UI.ToolBarHeight) || ((P.x + UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2) >= UI.DrawingAreaWidth) || ((P.y + UI.CONDITIONAL_VERTICAL_DIAGONAL) >= UI.height - UI.StatusBarHeight) || ((P.x - UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2) <= 0))
	{
		return true;
	}
}

void AddConditional::Execute()
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


	Conditional* pConditional = new Conditional(Position, LHS, ComparisonOperator, RHS);
	

	pManager->AddStatement(pConditional); // Adds the created statement to application manger's statement list
}