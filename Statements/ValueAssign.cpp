#include "ValueAssign.h"
#include <sstream>

using namespace std;

ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;
	

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	

	RightLoopInlet.x = LeftCorner.x + UI.ASSGN_WDTH;
	RightLoopInlet.y = LeftCorner.y + UI.ASSGN_HI / 2;
}

void ValueAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
	
}


//This function should be called when LHS or RHS changes
void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<LHS<<" = "<<RHS;	
	Text = T.str();	 
}

void ValueAssign::Save(ofstream& OutFile)
{
	OutFile << "VALUE_ASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y <<
		LHS << " " << RHS << '\n';
}

void ValueAssign::Load(ifstream& InFile)
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

bool ValueAssign::IsClickInside(Point p)
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

void ValueAssign::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("Please enter the variable name");
	LHS = pIn->GetVariable(pOut);


	pOut->PrintMessage("Please enter the value");
	RHS = pIn->GetValue(pOut);

	UpdateStatementText();
}

Point ValueAssign::getInlet() const
{
	return Inlet;
}

Point ValueAssign::getOutlet() const
{
	return Outlet;
}

Statement* ValueAssign::Clone() const
{
	return new ValueAssign(LeftCorner, LHS, RHS);	
}

void ValueAssign::setDrawingPoint(Point P)
{
	LeftCorner = P;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

int ValueAssign::getID() const
{
	return ID;
}

int ValueAssign::getEnteringConnectorCount() const
{
	return EnteringConnectorCount;
}

void ValueAssign::incrementEnteringConnectorCount()
{
	EnteringConnectorCount++;
}

int ValueAssign::getExitingConnectorCount() const
{
	return ExitingConnectorCount;
}

void ValueAssign::incrementExitingConnectorCount()
{
	ExitingConnectorCount++;
}



Point ValueAssign::getRightLoopInlet() const
{
	return RightLoopInlet;
}

void ValueAssign::DecrementEnteringConnectorCount()
{
	EnteringConnectorCount--;
}

void ValueAssign::DecrementExitingConnectorCount()
{
	ExitingConnectorCount--;
}

int ValueAssign::Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut) {
    int idx = -1;
    for (int i = 0; i < varCount; ++i) {
        if (varNames[i] == LHS) { idx = i; break; }
    }
    if (idx == -1 || !varDeclared[idx]) {
        pOut->PrintMessage((std::string("Run Error: variable '") + LHS + "' used before declaration").c_str());
        return 0;
    }
    varValues[idx] = RHS;
    varInitialized[idx] = true;
    return 0;
}