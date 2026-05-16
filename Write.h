#pragma once

#include "Statement.h"

class Write : public Statement
{
private:
	string variableOrValue; // depending on what need to be read

	Connector* pOutConn;


	Point Inlet;

	Point Outlet;

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Write(Point Lcorner, string varOrval = "");

	void setVariableOrValue(const string& varOrval);

	virtual void Draw(Output* pOut) const;

	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& InFile);

	virtual bool IsClickInside(Point p);

	virtual void Edit(Output* pOut, Input* pIn);

	virtual Point getInlet() const;

	virtual Point getOutlet() const;

	virtual Statement* Clone() const;

	virtual void setDrawingPoint(Point P);

	virtual int getID() const;

	virtual int getEnteringConnectorCount() const;

	virtual void incrementEnteringConnectorCount();

	virtual int getExitingConnectorCount() const;

	virtual void incrementExitingConnectorCount();

	virtual Point getRightLoopInlet() const;

	virtual void DecrementEnteringConnectorCount();

	virtual void DecrementExitingConnectorCount();
	
	virtual int Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut);
};
