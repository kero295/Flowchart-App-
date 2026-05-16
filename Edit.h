#pragma once

#include "Action.h"


class Edit : public Action
{

public:
	Edit(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();

};

