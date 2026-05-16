#pragma once

#pragma once

#include "Action.h"
#include "Write.h"

class AddWrite : public Action
{
private:

	Point Position;
	string variableOrValue;

public:
	AddWrite(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();
};