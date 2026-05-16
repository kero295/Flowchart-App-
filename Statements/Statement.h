#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "..\Connector.h"
//class Output;
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include <fstream>
#include <string>

//Base class for all Statements
class Statement
{
protected:
    int ID;			//Each Statement has an ID --> must be unique
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart
	static int Count; //static variable to keep track of the number of statements
	int EnteringConnectorCount; // counter for connectors that go to this statement
	int ExitingConnectorCount;  // counter for connectors that go out of this statement
	Point RightLoopInlet;

	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

	/// Add more parameters if needed.

public:
	Statement();
	void SetSelected(bool s);
	bool IsSelected() const;

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	
	

	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type

	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &InFile) = 0;	//Load the Statement parameters from a file

	virtual void Edit(Output* pOut, Input* pIn) = 0;		//Edit the Statement parameter
	
	
	// Execute the statement in the simulation mode (default no-op)
	virtual int Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut) = 0;
	

	//[BONUS] virtual void GenerateCode(ofstream &OutFile) = 0;
	virtual void GenerateCode(ofstream& OutFile) { }

	///TODO: Add more functions if needed

	static void ResetCount();

	// Expose statement text for the simulator/validator
	virtual string GetText() const { return Text; }

	virtual bool IsClickInside(Point p) = 0;

	virtual Point getInlet() const = 0;

	virtual Point getOutlet() const = 0;
	 
	virtual Point getRightLoopInlet() const = 0;

	virtual Statement* Clone() const = 0;

	virtual void setDrawingPoint(Point P) = 0;

	virtual int getID() const = 0;

	virtual int getEnteringConnectorCount() const = 0;

	virtual void incrementEnteringConnectorCount() = 0;

	virtual int getExitingConnectorCount() const = 0;

	virtual void incrementExitingConnectorCount() = 0;

	virtual void DecrementEnteringConnectorCount() = 0;

	virtual void DecrementExitingConnectorCount() = 0;
};

#endif