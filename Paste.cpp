#include "Paste.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Paste::Paste(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

bool Paste::IsDrawnOnUI(Point P)
{
	return false;
}

void Paste::ReadActionParameters()
{
}

void Paste::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Select a place to copy");

	pIn->GetPointClicked(Position);

	if (pManager->GetClipboard() == NULL) //no statement is copied
	{
		pOut->PrintMessage("No Statement Copied to Paste");
		return;
	}
	else 
	{

		Statement* NewStatement = (pManager->GetClipboard())->Clone(); //create a new statement using the clone function
		//Set the new position
		NewStatement->setDrawingPoint(Position);
		pManager->AddStatement(NewStatement); //add the new statement to the statement list
		pOut->PrintMessage("Statement Pasted");

		//Update the Interface
		pManager->UpdateInterface();
	}	


}

