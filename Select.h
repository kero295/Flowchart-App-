#pragma once

#include "Action.h"


class Select : public Action
{
private:

	Point Position;	

public:
	Select(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();

};

