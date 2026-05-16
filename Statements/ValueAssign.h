#ifndef VALUE_ASSIGN_H
#define VALUE_ASSIGN_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class ValueAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)
	

	Point Inlet;	//A point where connections enters this statement 
	                //It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	                //It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	
public:
	ValueAssign(Point Lcorner, string LeftHS="", double RightHS=0);
	
	void setLHS(const string &L);
	void setRHS(double R);

	virtual void Draw(Output* pOut) const;

	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& InFile);

	virtual bool IsClickInside(Point p);

	virtual void Edit(Output* pOut, Input* pIn);

	virtual Point getInlet() const;

	virtual Point getOutlet() const;

	virtual int Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut);

	virtual int getID() const;

	virtual Statement* Clone() const;

	virtual void setDrawingPoint(Point P);

	virtual int getEnteringConnectorCount() const;

	virtual void incrementEnteringConnectorCount();

	virtual int getExitingConnectorCount() const;

	virtual void incrementExitingConnectorCount();

	virtual void DecrementEnteringConnectorCount();

	virtual void DecrementExitingConnectorCount();

	virtual Point getRightLoopInlet() const;
};

#endif