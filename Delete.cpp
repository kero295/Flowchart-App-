#include "Delete.h"
#include "Start.h"
#include "End.h"
#include "Conditional.h"


#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Delete::Delete(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Delete::ReadActionParameters()
{
}

bool Delete::IsDrawnOnUI(Point P)
{
	return false;
}

void Delete::Execute()
{

	Output* pOut = pManager->GetOutput();
	Statement* SelectedStatement = pManager->GetSelectedStatement();
	Connector* SelectedConnector = pManager->GetSelectedConnector();

	if (SelectedStatement == NULL && SelectedConnector == NULL)
	{
		pOut->PrintMessage("No Statement or Connector selected to delete");
		return;
	}
	else if (SelectedStatement != NULL && SelectedConnector == NULL)
	{
		pManager->DeleteStatement(SelectedStatement);
		pManager->SetSelectedStatement(NULL);
	}
	else if (SelectedStatement == NULL && SelectedConnector != NULL)
	{
		SelectedConnector->getSrcStat()->DecrementExitingConnectorCount();
		pManager->DeleteConnector(SelectedConnector);
		pManager->SetSelectedConnector(NULL);
	}

}

