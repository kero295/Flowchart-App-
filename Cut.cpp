#include "Cut.h"
#include "Start.h"
#include "End.h"
#include "Conditional.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Cut::Cut(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Cut::ReadActionParameters()
{
}

bool Cut::IsDrawnOnUI(Point P)
{
	return false;
}

void Cut::Execute()
{
	
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter


	if (pManager->GetSelectedStatement() == NULL) //no statement is copied
	{
		pOut->PrintMessage("No Statement selected to cut");
		return;
	}
	else
	{
		Statement* SelectedStatement = pManager->GetSelectedStatement();

		pManager->SetClipboard(SelectedStatement); //set the clipboard to the selected statement
		pOut->PrintMessage("Statement cutted to Clipboard");

		pManager->DeleteStatement(SelectedStatement);
	}
	

}

