#include "Start.h"
#include <sstream>

using namespace std;

Start::Start(Point Lcorner)
{


	LeftCorner = Lcorner;


	Inlet.x = LeftCorner.x + UI.STARTEND_HORIZONTAL_DIAMETER/ 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.STARTEND_VERTICAL_DIAMETER;


	RightLoopInlet.x = LeftCorner.x + UI.STARTEND_HORIZONTAL_DIAMETER;
	RightLoopInlet.y = LeftCorner.y + UI.STARTEND_VERTICAL_DIAMETER / 2;
}




void Start::Draw(Output* pOut) const
{
 	
	pOut->DrawStart(LeftCorner, UI.STARTEND_HORIZONTAL_DIAMETER, UI.STARTEND_VERTICAL_DIAMETER, Selected);

}

void Start::Save(ofstream& OutFile)
{
	OutFile << "STRT" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << '\n';
}

void Start::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y;

	Outlet.x = LeftCorner.x + UI.STARTEND_HORIZONTAL_DIAMETER / 2;
	Outlet.y = LeftCorner.y + UI.STARTEND_VERTICAL_DIAMETER;

	Inlet.x = Outlet.x;
	Inlet.y = LeftCorner.y;


	RightLoopInlet.x = LeftCorner.x + UI.STARTEND_HORIZONTAL_DIAMETER;
	RightLoopInlet.y = LeftCorner.y + UI.STARTEND_VERTICAL_DIAMETER / 2;

	UpdateStatementText();
}


//This function should be called when LHS or RHS changes
void Start::UpdateStatementText()
{

}

bool Start::IsClickInside(Point p)
{
	if (p.x >= LeftCorner.x && p.x <= LeftCorner.x + UI.STARTEND_HORIZONTAL_DIAMETER)
	{
		if (p.y >= LeftCorner.y && p.y <= LeftCorner.y + UI.STARTEND_VERTICAL_DIAMETER)
		{
			return true;
		}
	}

	return false;
}

void Start::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("Can't edit a start statement");
}

Point Start::getInlet() const
{
	return Inlet;
}

Point Start::getOutlet() const
{
	return Outlet;
}

Statement* Start::Clone() const
{
	return new Start(LeftCorner);
}

void Start::setDrawingPoint(Point P)
{
	LeftCorner = P;

	Inlet.x = LeftCorner.x + UI.STARTEND_HORIZONTAL_DIAMETER / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.STARTEND_VERTICAL_DIAMETER;
}

int Start::getID() const
{
	return ID;
}

int Start::getEnteringConnectorCount() const
{
	return EnteringConnectorCount;
}

void Start::incrementEnteringConnectorCount()
{
	EnteringConnectorCount++;
}

int Start::getExitingConnectorCount() const
{
	return ExitingConnectorCount;
}

void Start::incrementExitingConnectorCount()
{
	ExitingConnectorCount++;
}


Point Start::getRightLoopInlet() const
{
	return RightLoopInlet;
}

void Start::DecrementEnteringConnectorCount()
{
	EnteringConnectorCount--;
}

void Start::DecrementExitingConnectorCount()
{
	ExitingConnectorCount--;
}

int Start::Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut) {
    // Start has no runtime effect
    return 0;
}