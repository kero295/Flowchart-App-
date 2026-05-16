#pragma once

#include "Action.h"
#include "Connector.h"

class AddConnector : public Action
{
private:
	Point firstClick;
	Point secondClick;
	Statement* Source;
	Statement* Distination;

public:
	AddConnector(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();
};