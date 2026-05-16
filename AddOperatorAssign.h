#pragma once

#include "Action.h"
#include "OperatorAssign.h"


class AddOperatorAssign : public Action
{
private:


	Point Position;	//Position where the user clicks to add the stat.

	string Left_Var;
	string Right_Var1;
	string Right_Var2;
	string Right_Op;

public:
	AddOperatorAssign(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();

};
