#pragma once

#include "Action.h"


class GenerateCppCode : public Action
{
private:
	string filename;
public:
	GenerateCppCode(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	virtual bool IsDrawnOnUI(Point P);

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

