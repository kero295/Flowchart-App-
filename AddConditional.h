#pragma once

#include "Action.h"
#include "Conditional.h"

class AddConditional : public Action
{
private:
	Point Position;

	string LHS;	//Left Handside
	string ComparisonOperator;
	string RHS;	//Right Handside

public:
	AddConditional(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	virtual void Execute();

};
