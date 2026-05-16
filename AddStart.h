#pragma once

#include "Action.h"
#include "Start.h"


class AddStart : public Action
{
private:


	Point Position;	//Position where the user clicks to add the stat.



public:
	AddStart(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();

};