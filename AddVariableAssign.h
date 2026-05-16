#pragma once

#include "Action.h"
#include "VarAssign.h"


class AddVarAssign : public Action
{
private:


	Point Position;	//Position where the user clicks to add the stat.

	string leftvar;
	string rightvar;

public:
	AddVarAssign(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();

};