#include "Switch.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Switch::Switch(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Switch::ReadActionParameters()
{
}

bool Switch::IsDrawnOnUI(Point P)
{
	return false;
}

void Switch::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();


	if (UI.AppMode == DESIGN) {

		pOut->PrintMessage("You are in simulation Mode");
		pOut->CreateSimulationToolBar();
		pManager->UpdateInterface();

	}
	else
	{

		pOut->PrintMessage("You are in design Mode");
		pOut->CreateDesignToolBar();
		pManager->UpdateInterface();

	}

}

