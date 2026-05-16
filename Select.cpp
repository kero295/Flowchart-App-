#include "Select.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Select::Select(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

bool Select::IsDrawnOnUI(Point P)
{
	return false;
}

void Select::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Select a statement");

	pIn->GetPointClicked(Position);
}

void Select::Execute()
{
	ReadActionParameters();

	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();


	Statement* SelectedStatement = pManager->GetStatement(Position); //current statement
	Connector* SelectedConnector = pManager->GetConnector(Position); //current connector

	if (SelectedStatement == NULL && SelectedConnector == NULL)
	{
		pOut->PrintMessage("Nothing Selected");
		return;
	}

	else if (SelectedStatement == pManager->GetSelectedStatement() && SelectedStatement != NULL) //handling if the user choose the same statement again to unselect it.
	{
		SelectedStatement->SetSelected(false);
		pManager->SetSelectedStatement(NULL);
		pManager->UpdateInterface();
	}

	else if (SelectedConnector == pManager->GetSelectedConnector() && SelectedConnector != NULL)
	{
		SelectedConnector->SetSelected(false);
		pManager->SetSelectedConnector(NULL);
		pManager->UpdateInterface();
	}

	else if (SelectedStatement != NULL && SelectedConnector == NULL)
	{
		if (pManager->GetSelectedStatement() != NULL) { //if the user click to a new statment, we should unselect the previous selected statement. 
			(pManager->GetSelectedStatement())->SetSelected(false);
		}

		if (pManager->GetSelectedConnector() != NULL) { //if the user click to a new connector, we should unselect the previous selected connector. 
			(pManager->GetSelectedConnector())->SetSelected(false);
		}

		SelectedStatement->SetSelected(true);
		pManager->SetSelectedStatement(SelectedStatement);
		pManager->UpdateInterface();
	}

	else if (SelectedConnector != NULL && SelectedStatement == NULL)
	{
		if (pManager->GetSelectedConnector() != NULL) { //if the user click to a new connector, we should unselect the previous selected connector. 
			(pManager->GetSelectedConnector())->SetSelected(false);
		}

		if (pManager->GetSelectedStatement() != NULL) { //if the user click to a new statment, we should unselect the previous selected statement. 
			(pManager->GetSelectedStatement())->SetSelected(false);
		}

		SelectedConnector->SetSelected(true);
		pManager->SetSelectedConnector(SelectedConnector);
		pManager->UpdateInterface();
	}

}