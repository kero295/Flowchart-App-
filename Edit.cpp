#include "Edit.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Edit::Edit(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Edit::ReadActionParameters()
{
}

bool Edit::IsDrawnOnUI(Point P)
{
	return false;
}

void Edit::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	if (pManager->GetSelectedStatement() == NULL) {
		pOut->PrintMessage("Select a statement first");
		return;
	}

	(pManager->GetSelectedStatement())->Edit(pOut,pIn);
}


