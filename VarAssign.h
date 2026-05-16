#pragma once

#include "Statement.h"


class VarAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (Value)

	

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	VarAssign(Point Lcorner, string LeftHS = "", string RightHS = 0);

	void setLHS(const string& L);
	void setRHS(string R);

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
