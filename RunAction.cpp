#include "RunAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
RunAction::RunAction(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

bool RunAction::IsDrawnOnUI(Point P)
{
	return false;
}

void RunAction::ReadActionParameters()
{

}

void RunAction::Execute()
{
	pManager->RunChart();
}

