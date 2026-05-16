#pragma once

#include "Statement.h"


class Conditional : public Statement
{
private:
	string LHS;	//Left Handside of the assignment
	string ComparisonOperator;
	string RHS;	//Right Handside
	int RightLoopConnectorCount;
	int RightConnectorCount;
	int LeftConnectorCount;
	bool LoopExist;

	

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point LeftOutlet;	//A point a connection leaves this statement
	Point RightOutlet;
	//It's used as the (Start) point of the (Output) connector

	Point TopPoint;	//top point of the statement block.

	virtual void UpdateStatementText();

public:
	Conditional(Point Top, string LeftHS = "", string op = "==", string RightHS = "");

	void setLHS(const string& L);
	void setOperation(const string& op);
	void setRHS(double R);

	virtual void Draw(Output* pOut) const;

	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& InFile);

	virtual bool IsClickInside(Point p);

	virtual void Edit(Output* pOut, Input* pIn);

	virtual Point getInlet() const;

	virtual Point getOutlet() const;

	Point getRightOutlet() const;

	virtual Statement* Clone() const;

	virtual void setDrawingPoint(Point P);

	virtual int getID() const;

	virtual int getEnteringConnectorCount() const;

	virtual void incrementEnteringConnectorCount();

	virtual int getExitingConnectorCount() const; // right side

	virtual void incrementExitingConnectorCount(); // right side

	int getRightLoopConnectorCount() const;

	void incrementRightLoopConnectorCount();

	int getLeftConnectorCount() const;

	void incrementLeftConnectorCount();

	virtual Point getRightLoopInlet() const;

	virtual void DecrementEnteringConnectorCount();

	virtual void DecrementExitingConnectorCount();
	
	bool getLoopExist() const;
	
	void setLoopExist(bool l);

	virtual int Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut);
};

