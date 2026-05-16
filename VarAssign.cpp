#include "VarAssign.h"
#include <sstream>

using namespace std;

VarAssign::VarAssign(Point Lcorner, string LeftHS, string RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;


	RightLoopInlet.x = LeftCorner.x + UI.ASSGN_WDTH;
	RightLoopInlet.y = LeftCorner.y + UI.ASSGN_HI / 2;
}

void VarAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void VarAssign::setRHS(string R)
{
	RHS = R;
	UpdateStatementText();
}


void VarAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}


//This function should be called when LHS or RHS changes
void VarAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}

void VarAssign::Save(ofstream& OutFile)
{
	OutFile << "VARIABLE_ASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y <<
		LHS << " " << RHS << '\n';
}

void VarAssign::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;


	RightLoopInlet.x = LeftCorner.x + UI.ASSGN_WDTH;
	RightLoopInlet.y = LeftCorner.y + UI.ASSGN_HI / 2;

	UpdateStatementText();
}

bool VarAssign::IsClickInside(Point p)
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

void VarAssign::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("Please enter the variable name");
	LHS = pIn->GetVariable(pOut);

	
	pOut->PrintMessage("Please enter the variable");
	RHS = pIn->GetVariable(pOut);

	UpdateStatementText();
}

Point VarAssign::getInlet() const
{
	return Inlet;
}

Point VarAssign::getOutlet() const
{
	return Outlet;
}

Statement* VarAssign::Clone() const
{
	return new VarAssign(LeftCorner, LHS, RHS);
}

void VarAssign::setDrawingPoint(Point P)
{
	LeftCorner = P;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

int VarAssign::getID() const
{
	return ID;
}

int VarAssign::getEnteringConnectorCount() const
{
	return EnteringConnectorCount;
}

void VarAssign::incrementEnteringConnectorCount()
{
	EnteringConnectorCount++;
}

int VarAssign::getExitingConnectorCount() const
{
	return ExitingConnectorCount;
}

void VarAssign::incrementExitingConnectorCount()
{
	ExitingConnectorCount++;
}


Point VarAssign::getRightLoopInlet() const
{
	return RightLoopInlet;
}

void VarAssign::DecrementEnteringConnectorCount()
{
	EnteringConnectorCount--;
}

void VarAssign::DecrementExitingConnectorCount()
{
	ExitingConnectorCount--;
}

int VarAssign::Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut) {
    int idx = -1;
    for (int i = 0; i < varCount; ++i) {
        if (varNames[i] == LHS) { idx = i; break; }
    }
    if (idx == -1 || !varDeclared[idx]) { pOut->PrintMessage((std::string("Run Error: variable '") + LHS + "' used before declaration").c_str()); return 0; }
    int ridx = -1;
    for (int i = 0; i < varCount; ++i) {
        if (varNames[i] == RHS) { ridx = i; break; }
    }
    if (ridx == -1 || !varInitialized[ridx]) { pOut->PrintMessage((std::string("Run Error: variable '") + RHS + "' used before initialization").c_str()); return 0; }
    varValues[idx] = varValues[ridx]; varInitialized[idx] = true;
    return 0;
}