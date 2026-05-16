#pragma once

#include "Action.h"
#include "End.h"


class AddEnd : public Action
{
private:
	

	Point Position;	//Position where the user clicks to add the stat.



public:
	AddEnd(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();

};