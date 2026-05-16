#pragma once

#include "Action.h"
#include "DeclareVariable.h"

class AddDeclareVariable : public Action
{
private:
	Point Position;
	string variable;

public:
	AddDeclareVariable(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();
};
