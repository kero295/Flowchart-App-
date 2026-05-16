#include "Copy.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Copy::Copy(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Copy::ReadActionParameters()
{
}

bool Copy::IsDrawnOnUI(Point P)
{
	return false;
}

void Copy::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	Statement* SelectedStatement = pManager->GetSelectedStatement();

	if (SelectedStatement == NULL) //no statement is selected
	{
		pOut->PrintMessage("No Statement Selected to Copy");
		return;
	}
	else {
		pManager->SetClipboard(SelectedStatement->Clone()); //set the clipboard to the selected statement
		pOut->PrintMessage("Statement Copied to Clipboard");
	}



}

