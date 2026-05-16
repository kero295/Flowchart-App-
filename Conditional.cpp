#include "Conditional.h"
#include <sstream>

using namespace std;

Conditional::Conditional(Point Top, string LeftHS, string op, string RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;
	ComparisonOperator = op;
	RightLoopConnectorCount = 0;
	RightConnectorCount = 0;
	LeftConnectorCount = 0;
	LoopExist = false;

	UpdateStatementText();

	TopPoint = Top;


	Inlet.x = TopPoint.x;
	Inlet.y = TopPoint.y;

	LeftOutlet.x = Inlet.x - UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2;
	LeftOutlet.y = TopPoint.y + UI.CONDITIONAL_VERTICAL_DIAGONAL / 2;

	RightOutlet.x = Inlet.x + UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2;
	RightOutlet.y = TopPoint.y + UI.CONDITIONAL_VERTICAL_DIAGONAL / 2;



	RightLoopInlet.x = TopPoint.x + UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2;
	RightLoopInlet.y = TopPoint.y + UI.CONDITIONAL_VERTICAL_DIAGONAL / 2;
}

void Conditional::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void Conditional::setOperation(const string& op)
{
	ComparisonOperator = op;
	UpdateStatementText();
}

void Conditional::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void Conditional::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawConditional(TopPoint, UI.CONDITIONAL_HORIZONTAL_DIAGONAL, UI.CONDITIONAL_VERTICAL_DIAGONAL, Text, Selected);
}


//This function should be called when LHS or RHS changes
void Conditional::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " " << ComparisonOperator << " " << RHS;
	Text = T.str();
}

void Conditional::Save(ofstream& OutFile)
{
	OutFile << "COND " << ID << " " << TopPoint.x << " " << TopPoint.y << " " << LHS << " " << ComparisonOperator << " " << RHS << '\n';
}

void Conditional::Load(ifstream& InFile)
{
	InFile >> ID >> TopPoint.x >> TopPoint.y >> LHS >> ComparisonOperator >> RHS;

	Inlet.x = TopPoint.x;
	Inlet.y = TopPoint.y;

	LeftOutlet.x = Inlet.x - UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2;
	LeftOutlet.y = TopPoint.y + UI.CONDITIONAL_VERTICAL_DIAGONAL / 2;

	RightOutlet.x = Inlet.x + UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2;
	RightOutlet.y = TopPoint.y + UI.CONDITIONAL_VERTICAL_DIAGONAL / 2;



	RightLoopInlet.x = TopPoint.x + UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2;
	RightLoopInlet.y = TopPoint.y + UI.CONDITIONAL_VERTICAL_DIAGONAL / 2;

	UpdateStatementText();
}

bool Conditional::IsClickInside(Point p)
{
	int verticalHelper = UI.CONDITIONAL_VERTICAL_DIAGONAL / 4; // helsps in the offsetting
	int horizontalHelper = UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 4; // helsps in the offsetting

	if (p.x >= TopPoint.x - horizontalHelper && p.x <= TopPoint.x + horizontalHelper && p.y >= TopPoint.y && p.y <= TopPoint.y + UI.CONDITIONAL_VERTICAL_DIAGONAL)
	{
		return true;
	}
	else if (p.x >= TopPoint.x - UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2 && p.x <= TopPoint.x + UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2 && p.y >= TopPoint.y + verticalHelper && p.y <= TopPoint.y + verticalHelper * 3)
	{
		return true;
	}

	return false;
}

void Conditional::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("Please enter the left hand side");
	LHS = pIn->GetVariableOrValue(pOut);


	pOut->PrintMessage("Please enter the comparison operator");
	ComparisonOperator = pIn->GetCompOperator(pOut);

	pOut->PrintMessage("Please enter the right hand side");
	RHS = pIn->GetVariableOrValue(pOut);

	UpdateStatementText();
}

Point Conditional::getInlet() const
{
	return Inlet;
}

Point Conditional::getOutlet() const
{
	return LeftOutlet;
}

Point Conditional::getRightOutlet() const
{
	return RightOutlet;
}

Statement* Conditional::Clone() const
{
	return new Conditional(TopPoint, LHS, ComparisonOperator, RHS);
}

void Conditional::setDrawingPoint(Point P)
{
	TopPoint = P;

	Inlet.x = TopPoint.x;
	Inlet.y = TopPoint.y;

	LeftOutlet.x = Inlet.x - UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2;
	LeftOutlet.y = TopPoint.y + UI.CONDITIONAL_VERTICAL_DIAGONAL / 2;

	RightOutlet.x = Inlet.x + UI.CONDITIONAL_HORIZONTAL_DIAGONAL / 2;
	RightOutlet.y = TopPoint.y + UI.CONDITIONAL_VERTICAL_DIAGONAL / 2;
}

int Conditional::getID() const
{
	return ID;
}

int Conditional::getEnteringConnectorCount() const
{
	return EnteringConnectorCount;
}

void Conditional::incrementEnteringConnectorCount()
{
	EnteringConnectorCount++;
}

int Conditional::getExitingConnectorCount() const // right side
{
	return RightConnectorCount + LeftConnectorCount;
}

void Conditional::incrementExitingConnectorCount() // right side
{
	RightConnectorCount++;
}

int Conditional::getRightLoopConnectorCount() const
{
	return RightLoopConnectorCount;
}

void Conditional::incrementRightLoopConnectorCount()
{
	RightLoopConnectorCount++;
}



int Conditional::getLeftConnectorCount() const
{
	return LeftConnectorCount;
}

void Conditional::incrementLeftConnectorCount()
{
	LeftConnectorCount++;
}



Point Conditional::getRightLoopInlet() const
{
	return Inlet;
}

void Conditional::DecrementEnteringConnectorCount()
{
	EnteringConnectorCount--;
}

void Conditional::DecrementExitingConnectorCount()
{
	ExitingConnectorCount--;
}

bool Conditional::getLoopExist() const
{
	return LoopExist;
}

void Conditional::setLoopExist(bool l)
{
	LoopExist = l;
}

int Conditional::Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut) {
    auto findVar = [&](const std::string &name) -> int { for (int i = 0; i < varCount; ++i) if (varNames[i] == name) return i; return -1; };
    double lv = 0, rv = 0; bool lok = false, rok = false;
    try { lv = stod(LHS); lok = true; } catch(...) { lok = false; }
    if (!lok) { int idx = findVar(LHS); if (idx == -1 || !varInitialized[idx]) { pOut->PrintMessage((std::string("Run Error: variable '") + LHS + "' used before initialization").c_str()); return 0; } lv = varValues[idx]; }
    try { rv = stod(RHS); rok = true; } catch(...) { rok = false; }
    if (!rok) { int idx = findVar(RHS); if (idx == -1 || !varInitialized[idx]) { pOut->PrintMessage((std::string("Run Error: variable '") + RHS + "' used before initialization").c_str()); return 0; } rv = varValues[idx]; }
    bool cond = false;
    if (ComparisonOperator == "==") cond = (lv == rv);
    else if (ComparisonOperator == "!=") cond = (lv != rv);
    else if (ComparisonOperator == ">") cond = (lv > rv);
    else if (ComparisonOperator == "<") cond = (lv < rv);
    else if (ComparisonOperator == ">=") cond = (lv >= rv);
    else if (ComparisonOperator == "<=") cond = (lv <= rv);
    return cond ? 1 : 2;
}

