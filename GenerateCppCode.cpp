#include "GenerateCppCode.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
GenerateCppCode::GenerateCppCode(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

bool GenerateCppCode::IsDrawnOnUI(Point P)
{
	return false;
}

void GenerateCppCode::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Enter filename for C++ code: ");
	filename = pIn->GetString(pOut);
}

void GenerateCppCode::Execute()
{
	ReadActionParameters();

   pManager->GenerateCode(filename);
}


