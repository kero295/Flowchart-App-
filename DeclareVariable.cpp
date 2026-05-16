#include "DeclareVariable.h"
#include <sstream>

using namespace std;

DeclareVariable::DeclareVariable(Point Lcorner, string var, double RightHS)
{
	variable = var;

	UpdateStatementText();

	LeftCorner = Lcorner;


	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;


	RightLoopInlet.x = LeftCorner.x + UI.ASSGN_WDTH;
	RightLoopInlet.y = LeftCorner.y + UI.ASSGN_HI / 2;
}

void DeclareVariable::setLHS(const string& var)
{
	variable = var;
	UpdateStatementText();
}


void DeclareVariable::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void DeclareVariable::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << "double " << variable;
	Text = T.str();
}

void DeclareVariable::Save(ofstream& OutFile)
{
	OutFile << "DECLARE " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << variable << '\n';
}

void DeclareVariable::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> variable;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;


	RightLoopInlet.x = LeftCorner.x + UI.ASSGN_WDTH;
	RightLoopInlet.y = LeftCorner.y + UI.ASSGN_HI / 2;

	UpdateStatementText();
}


bool DeclareVariable::IsClickInside(Point p)
{
	if (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.ASSGN_WDTH)
	{
		if (p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.ASSGN_HI)
		{
			return true;
		}
	}

	return false;
}

void DeclareVariable::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("Please enter the variable name");
	variable = pIn->GetVariable(pOut);

	UpdateStatementText();
}

Point DeclareVariable::getInlet() const
{
	return Inlet;
}

Point DeclareVariable::getOutlet() const
{
	return Outlet;
}

Statement* DeclareVariable::Clone() const
{
	return new DeclareVariable(LeftCorner, variable);
}

void DeclareVariable::setDrawingPoint(Point P)
{
	LeftCorner = P;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

int DeclareVariable::getID() const
{
	return ID;
}

int DeclareVariable::getEnteringConnectorCount() const
{
	return EnteringConnectorCount;
}

void DeclareVariable::incrementEnteringConnectorCount()
{
	EnteringConnectorCount++;
}

int DeclareVariable::getExitingConnectorCount() const
{
	return ExitingConnectorCount;
}

void DeclareVariable::incrementExitingConnectorCount()
{
	ExitingConnectorCount++;
}



Point DeclareVariable::getRightLoopInlet() const
{
	return RightLoopInlet;
}

void DeclareVariable::DecrementEnteringConnectorCount()
{
	EnteringConnectorCount--;
}

void DeclareVariable::DecrementExitingConnectorCount()
{
	ExitingConnectorCount--;
}

int DeclareVariable::Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut) {
	// find variable index
	int idx = -1;
	for (int i = 0; i < varCount; ++i) {
		if (varNames[i] == variable) { idx = i; break; }
	}

	// add variable if not present
	//Omar

	if (idx != -1 && varDeclared[idx]) {
		// variable already declared
		return -1; // error
	}

	if (idx == -1 && varCount < 100) {
		varNames[varCount] = variable;
		varDeclared[varCount] = false;
		varInitialized[varCount] = false;
		idx = varCount;
		++varCount;
	}
	if (idx != -1) {
		varDeclared[idx] = true;
		varInitialized[idx] = false;
	}
	return 0;
}