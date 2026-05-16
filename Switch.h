#pragma once

#include "Action.h"


class Switch : public Action
{
private:

	Point Position;

public:
	Switch(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();

};



