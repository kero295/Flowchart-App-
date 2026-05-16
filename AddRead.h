#pragma once

#include "Action.h"
#include "Read.h"

class AddRead : public Action
{
private:

	Point Position;
	string variable;

public:
	AddRead(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();
};