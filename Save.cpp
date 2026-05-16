#include "Save.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Save::Save(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

bool Save::IsDrawnOnUI(Point P)
{
	return false;
}

void Save::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Please enter the file name");
	fileName = pIn->GetString(pOut);

}

void Save::Execute()
{
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();

	pManager->SaveFile(fileName);

	pOut->PrintMessage("Saved Successfully");
}

