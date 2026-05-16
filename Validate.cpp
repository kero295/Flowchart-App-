#include "Validate.h"
using namespace std;

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>


//constructor: set the ApplicationManager pointer inside this action
Validate::Validate(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

bool Validate::IsDrawnOnUI(Point P)
{
	return false;
}

void Validate::ReadActionParameters()
{

}

void Validate::Execute()
{
	pManager->ValidateChart();
}

