#include "End.h"
#include <sstream>

using namespace std;

End::End(Point Lcorner)
{


	LeftCorner = Lcorner;


	Inlet.x = LeftCorner.x + UI.STARTEND_HORIZONTAL_DIAMETER / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.STARTEND_VERTICAL_DIAMETER;


	RightLoopInlet.x = LeftCorner.x + UI.STARTEND_HORIZONTAL_DIAMETER;
	RightLoopInlet.y = LeftCorner.y + UI.STARTEND_VERTICAL_DIAMETER / 2;
}




void End::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawEnd(LeftCorner, UI.STARTEND_HORIZONTAL_DIAMETER, UI.STARTEND_VERTICAL_DIAMETER, Selected);

}


//This function should be called when LHS or RHS changes
void End::UpdateStatementText()
{

}

void End::Save(ofstream& OutFile)
{
	OutFile << "END" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << '\n';
}

void End::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y;

	Inlet.x = LeftCorner.x + UI.STARTEND_HORIZONTAL_DIAMETER / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.STARTEND_VERTICAL_DIAMETER;


	RightLoopInlet.x = LeftCorner.x + UI.STARTEND_HORIZONTAL_DIAMETER;
	RightLoopInlet.y = LeftCorner.y + UI.STARTEND_VERTICAL_DIAMETER / 2;

	UpdateStatementText();
}


bool End::IsClickInside(Point p)
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

void End::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("Can't edit an end statement");
}

Point End::getInlet() const
{
	return Inlet;
}

Point End::getOutlet() const
{
	return Outlet;
}

Statement* End::Clone() const
{
	return new End(LeftCorner);
}

void End::setDrawingPoint(Point P)
{
	LeftCorner = P;

	Inlet.x = LeftCorner.x + UI.STARTEND_HORIZONTAL_DIAMETER / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.STARTEND_VERTICAL_DIAMETER;
}

int End::getID() const
{
	return ID;
}

int End::getEnteringConnectorCount() const
{
	return EnteringConnectorCount;
}

void End::incrementEnteringConnectorCount()
{
	EnteringConnectorCount++;
}

int End::getExitingConnectorCount() const
{
	return ExitingConnectorCount;
}

void End::incrementExitingConnectorCount()
{
	ExitingConnectorCount++;
}



Point End::getRightLoopInlet() const
{
	return RightLoopInlet;
}

void End::DecrementEnteringConnectorCount()
{
	EnteringConnectorCount--;
}

void End::DecrementExitingConnectorCount()
{
	ExitingConnectorCount--;
}

int End::Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut) {
    // End terminates; nothing to do
    return 0;
}