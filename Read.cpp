#include "Read.h"
#include <sstream>

using namespace std;

Read::Read(Point Lcorner, string var)
{
	variable = var;

	UpdateStatementText();

	LeftCorner = Lcorner;


	Inlet.x = LeftCorner.x + UI.READWRITE_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.READWRITE_HEIGHT;


	RightLoopInlet.x = LeftCorner.x + UI.READWRITE_WIDTH;
	RightLoopInlet.y = LeftCorner.y + UI.READWRITE_HEIGHT / 2;
}

void Read::setVariable(const string& var)
{
	variable = var;
	UpdateStatementText();
}

void Read::Draw(Output* pOut) const
{
	pOut->DrawRead(LeftCorner, UI.READWRITE_WIDTH, UI.READWRITE_HEIGHT, Text, Selected);
}

void Read::UpdateStatementText()
{
	ostringstream T;
	T << "Read " << variable;
	Text = T.str();
}

void Read::Save(ofstream& OutFile)
{
	OutFile << "READ " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << variable << '\n';
}

void Read::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> variable;

	Inlet.x = LeftCorner.x + UI.READWRITE_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.READWRITE_HEIGHT;



	RightLoopInlet.x = LeftCorner.x + UI.READWRITE_WIDTH;
	RightLoopInlet.y = LeftCorner.y + UI.READWRITE_HEIGHT / 2;

	UpdateStatementText();
}

bool Read::IsClickInside(Point p)
{
	if (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.READWRITE_WIDTH && p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.READWRITE_HEIGHT / 2)
	{
		return true;
	}
	else if (p.x >= LeftCorner.x - UI.READWRITE_OFFSET && p.x <= LeftCorner.x - UI.READWRITE_OFFSET + UI.READWRITE_WIDTH && p.y > LeftCorner.y + UI.READWRITE_HEIGHT / 2 && p.y <= LeftCorner.y + UI.READWRITE_HEIGHT)
	{
		return true;
	}
	else if(p.x >= LeftCorner.x - UI.READWRITE_OFFSET && p.x <= LeftCorner.x && p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.READWRITE_HEIGHT / 2)
	{
		return true;
	}
	else if(p.x >= LeftCorner.x - UI.READWRITE_OFFSET + UI.READWRITE_WIDTH && p.x <= LeftCorner.x - UI.READWRITE_OFFSET / 2 + UI.READWRITE_WIDTH && p.y > LeftCorner.y + UI.READWRITE_HEIGHT / 2 && p.y <= LeftCorner.y + UI.READWRITE_HEIGHT)
	{
		return true;
	}

	return false;
}

void Read::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("Please enter the variable name");
	variable = pIn->GetVariable(pOut);

	UpdateStatementText();
}

Point Read::getInlet() const
{
	return Inlet;
}

Point Read::getOutlet() const
{
	return Outlet;
}

Statement* Read::Clone() const
{
	return new Read(LeftCorner, variable);
}

void Read::setDrawingPoint(Point P)
{
	LeftCorner = P;

	Inlet.x = LeftCorner.x + UI.READWRITE_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.READWRITE_HEIGHT;
}

int Read::getID() const
{
	return ID;
}

int Read::getEnteringConnectorCount() const
{
	return EnteringConnectorCount;
}

void Read::incrementEnteringConnectorCount()
{
	EnteringConnectorCount++;
}

int Read::getExitingConnectorCount() const
{
	return ExitingConnectorCount;
}

void Read::incrementExitingConnectorCount()
{
	ExitingConnectorCount++;
}



Point Read::getRightLoopInlet() const
{
	return RightLoopInlet;
}

void Read::DecrementEnteringConnectorCount()
{
	EnteringConnectorCount--;
}

void Read::DecrementExitingConnectorCount()
{
	ExitingConnectorCount--;
}

int Read::Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut) {
    // find variable index
    int idx = -1;
    for (int i = 0; i < varCount; ++i) {
        if (varNames[i] == variable) { idx = i; break; }
    }
    if (idx == -1 || !varDeclared[idx]) {
        pOut->PrintMessage((std::string("Run Error: variable '") + variable + "' used before declaration").c_str());
        return 0;
    }

    // show message in status bar and request value from the user
    pOut->PrintMessage("enter value for read:");
    double val = pIn->GetValue(pOut);

    // assign and mark initialized for future use
    varValues[idx] = val;
    varInitialized[idx] = true;
    return 0;
}