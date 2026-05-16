#include "Write.h"
#include <sstream>

using namespace std;

Write::Write(Point Lcorner, string varOrval)
{
	variableOrValue = varOrval;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.READWRITE_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.READWRITE_HEIGHT;

	RightLoopInlet.x = LeftCorner.x + UI.READWRITE_WIDTH;
	RightLoopInlet.y = LeftCorner.y + UI.READWRITE_HEIGHT / 2;
}

void Write::setVariableOrValue(const string& varOrval)
{
	variableOrValue = varOrval;
	UpdateStatementText();
}

void Write::Draw(Output* pOut) const
{
	pOut->DrawRead(LeftCorner, UI.READWRITE_WIDTH, UI.READWRITE_HEIGHT, Text, Selected);
}

void Write::UpdateStatementText()
{
	ostringstream T;
	T << "Write " << variableOrValue;
	Text = T.str();
}

void Write::Save(ofstream& OutFile)
{
	OutFile << "WRITE " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << variableOrValue << '\n';
}

void Write::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> variableOrValue;

	Inlet.x = LeftCorner.x + UI.READWRITE_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.READWRITE_HEIGHT;

	RightLoopInlet.x = LeftCorner.x + UI.READWRITE_WIDTH;
	RightLoopInlet.y = LeftCorner.y + UI.READWRITE_HEIGHT / 2;

	UpdateStatementText();

}

bool Write::IsClickInside(Point p)
{
	if (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.READWRITE_WIDTH && p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.READWRITE_HEIGHT / 2)
	{
		return true;
	}
	else if (p.x >= LeftCorner.x - UI.READWRITE_OFFSET && p.x <= LeftCorner.x - UI.READWRITE_OFFSET + UI.READWRITE_WIDTH && p.y > LeftCorner.y + UI.READWRITE_HEIGHT / 2 && p.y <= LeftCorner.y + UI.READWRITE_HEIGHT)
	{
		return true;
	}
	else if (p.x >= LeftCorner.x - UI.READWRITE_OFFSET && p.x <= LeftCorner.x && p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.READWRITE_HEIGHT / 2)
	{
		return true;
	}
	else if (p.x >= LeftCorner.x - UI.READWRITE_OFFSET + UI.READWRITE_WIDTH && p.x <= LeftCorner.x - UI.READWRITE_OFFSET / 2 + UI.READWRITE_WIDTH && p.y > LeftCorner.y + UI.READWRITE_HEIGHT / 2 && p.y <= LeftCorner.y + UI.READWRITE_HEIGHT)
	{
		return true;
	}

	return false;
}

void Write::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("Please enter the variable name");
	variableOrValue = pIn->GetVariable(pOut);

	UpdateStatementText();
}

Point Write::getInlet() const
{
	return Inlet;
}

Point Write::getOutlet() const
{
	return Outlet;
}

Statement* Write::Clone() const
{
	return new Write(LeftCorner, variableOrValue);
}

void Write::setDrawingPoint(Point P)
{
	LeftCorner = P;

	Inlet.x = LeftCorner.x + UI.READWRITE_WIDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.READWRITE_HEIGHT;
}

int Write::getID() const
{
	return ID;
}

int Write::getEnteringConnectorCount() const
{
	return EnteringConnectorCount;
}

void Write::incrementEnteringConnectorCount()
{
	EnteringConnectorCount++;
}

int Write::getExitingConnectorCount() const
{
	return ExitingConnectorCount;
}

void Write::incrementExitingConnectorCount()
{
	ExitingConnectorCount++;
}


Point Write::getRightLoopInlet() const
{
	return RightLoopInlet;
}

void Write::DecrementEnteringConnectorCount()
{
	EnteringConnectorCount--;
}

void Write::DecrementExitingConnectorCount()
{
	ExitingConnectorCount--;
}

int Write::Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut) {
    double v = 0; bool ok = false;
    try { v = stod(variableOrValue); ok = true; } catch(...) { ok = false; }
    if (ok) {
        outputAccum += variableOrValue + "\n";
    } else {
        int idx = -1;
        for (int i = 0; i < varCount; ++i) {
            if (varNames[i] == variableOrValue) { idx = i; break; }
        }
        if (idx == -1 || !varInitialized[idx]) {
            pOut->PrintMessage((std::string("Run Error: variable '") + variableOrValue + "' used before initialization").c_str());
            return 0;
        }
        outputAccum += std::to_string(varValues[idx]) + "\n";
    }
    return 0;
}