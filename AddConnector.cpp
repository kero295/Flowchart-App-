#include "AddConnector.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "Start.h"
#include "End.h"
#include "Conditional.h"

#include <sstream>
using namespace std;


//constructor: set the ApplicationManager pointer inside this action
AddConnector::AddConnector(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddConnector::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Connector Statement: Click on the first statement");
	pIn->GetPointClicked(firstClick);
	Point StartPoint = firstClick;
	Source = pManager->GetStatement(StartPoint);
	pOut->ClearStatusBar();


	pOut->PrintMessage("Connector Statement: Click on the second statement");
	pIn->GetPointClicked(secondClick);
	Point EndPoint = secondClick;
	Distination = pManager->GetStatement(EndPoint);
	pOut->ClearStatusBar();

	if (Source == NULL || Distination == NULL)
	{
		pOut->PrintMessage("Error: please select 2 statements");
		pIn->GetPointClicked(firstClick);
		pOut->ClearStatusBar();
		return;
	}

	if (dynamic_cast<Conditional*>(Source) == NULL || dynamic_cast<Conditional*>(Distination))
	{
		if (dynamic_cast<Start*>(Source) == NULL && dynamic_cast<End*>(Distination) == NULL)
		{
			if (Source->getExitingConnectorCount() == 1)
			{
				pOut->PrintMessage("Error: a statement can't have 2 connectors");
				Source = NULL;
				return;
			}
			else if (Distination->getExitingConnectorCount() == 1)
			{
				pOut->PrintMessage("Error: a statement can't have 2 connectors");
				Distination = NULL;
				return;
			}
		}
		else if (dynamic_cast<Start*>(Source) != NULL || dynamic_cast<End*>(Distination) != NULL)
		{
			if (Source->getExitingConnectorCount() == 1)
			{
				pOut->PrintMessage("Error: a statement can't have 2 connectors");
				Source = NULL;
				return;
			}
		
		}
	}

	if (dynamic_cast<Start*>(Distination))
	{
		pOut->PrintMessage("Error: Start can't be a Distination");
		Distination = NULL;
		return;
	}

	if (dynamic_cast<End*>(Source))
	{
		pOut->PrintMessage("Error: End can't be a Source");
		Source = NULL;
		return;
	}

	if (dynamic_cast<Conditional*>(Source) || dynamic_cast<Conditional*>(Distination))
	{
		if (Source->getExitingConnectorCount() == 1 && ((Conditional*)Source)->getLeftConnectorCount() == 1)
		{
			pOut->PrintMessage("Error: a condition can't have more that 2 exiting connectors");
			Source = NULL;
			return;
		}



		if ((((Conditional*)Source)->getRightLoopConnectorCount() == 1 && Source->getExitingConnectorCount() == 0 && StartPoint.x < EndPoint.x) ||
			(((Conditional*)Source)->getRightLoopConnectorCount() == 0 && Source->getExitingConnectorCount() == 1 && StartPoint.x < EndPoint.x))
		{
			pOut->PrintMessage("Error: a conditional side can't have  2 connector");
			Source = NULL;
			return;
		}

		if (((Conditional*)Source)->getLoopExist() && StartPoint.y > EndPoint.y)
		{
			pOut->PrintMessage("Error: a conditional can't have  2 loops");
			Source = NULL;
			return;
		}



		if (((Conditional*)Source)->getLeftConnectorCount() == 1 && StartPoint.x > EndPoint.x)
		{
			pOut->PrintMessage("Error: a conditional side can't have  2 connector");
			Source = NULL;
			return;
		}
		
	}

}

bool AddConnector::IsDrawnOnUI(Point P)
{
	return false;
}

void AddConnector::Execute()
{
	ReadActionParameters();

	if (Source == NULL || Distination == NULL)
	{
		return;
	}

	Connector* pConnector = new Connector(Source, Distination);

	if (dynamic_cast<Conditional*>(Source) && firstClick.y > secondClick.y)
	{
		((Conditional*)Source)->incrementRightLoopConnectorCount();
		((Conditional*)Source)->setLoopExist(true);
	}

	else if (dynamic_cast<Conditional*>(Source) && firstClick.y < secondClick.y && firstClick.x > secondClick.x)
	{
		((Conditional*)Source)->incrementLeftConnectorCount();
	}
	else
	{
		Source->incrementExitingConnectorCount();
	}
	Distination->incrementEnteringConnectorCount();

	pManager->AddConn(pConnector); // Adds the created statement to application manger's statement list
}