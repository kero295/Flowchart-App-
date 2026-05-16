#include "OperatorAssign.h"
#include <sstream>

using namespace std;

OperatorAssign::OperatorAssign(Point Lcorner, string LeftHS, string RightHS1, string RightHS2, string RightHS_op)
{

	LHS = LeftHS;
	RHS1 = RightHS1;	
	RHS2 = RightHS2; 
	RHS_op = RightHS_op;

	UpdateStatementText();

	LeftCorner = Lcorner;


	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;



	RightLoopInlet.x = LeftCorner.x + UI.ASSGN_WDTH;
	RightLoopInlet.y = LeftCorner.y + UI.ASSGN_HI / 2;
}

void OperatorAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void OperatorAssign::setRHS1(const string& R1)
{
	RHS1 = R1;
	UpdateStatementText();
}

void OperatorAssign::setRHS2(const string& R2)
{
	RHS2 = R2;
	UpdateStatementText();
}

void OperatorAssign::setRHS_op(const string& Rop)
{
	RHS_op = Rop;
	UpdateStatementText();
}




void OperatorAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

//This function should be called when LHS or RHS changes
void OperatorAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS1 << " " << RHS_op << " " << RHS2;
	Text = T.str();
}

void OperatorAssign::Save(ofstream& OutFile)
{
	OutFile << "OP_ASSIGN " << ID << " " << LeftCorner.x << " " << LeftCorner.y
		<< " " << LHS << " " << RHS1 << " " << RHS_op << " " << RHS2 << '\n';
}

void OperatorAssign::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS1 >> RHS_op >> RHS2;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;


	RightLoopInlet.x = LeftCorner.x + UI.ASSGN_WDTH;
	RightLoopInlet.y = LeftCorner.y + UI.ASSGN_HI / 2;

	UpdateStatementText();
}

bool OperatorAssign::IsClickInside(Point p)
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

void OperatorAssign::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("Please enter the variable name");
	LHS = pIn->GetVariable(pOut);


	pOut->PrintMessage("Please enter a variable or a value");
	RHS1 = pIn->GetVariableOrValue(pOut);

	pOut->PrintMessage("Please enter an operator");
	RHS_op = pIn->GetArithOperator(pOut);

	pOut->PrintMessage("Please enter a variable or a value");
	RHS2 = pIn->GetVariableOrValue(pOut);

	UpdateStatementText();
}

Point OperatorAssign::getInlet() const
{
	return Inlet;
}

Point OperatorAssign::getOutlet() const
{
	return Outlet;
}

Statement* OperatorAssign::Clone() const
{
	return new OperatorAssign(LeftCorner, LHS, RHS1, RHS_op, RHS2);
}

void OperatorAssign::setDrawingPoint(Point P)
{
	LeftCorner = P;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

int OperatorAssign::getID() const
{
	return ID;
}

int OperatorAssign::getEnteringConnectorCount() const
{
	return EnteringConnectorCount;
}

void OperatorAssign::incrementEnteringConnectorCount()
{
	EnteringConnectorCount++;
}

int OperatorAssign::getExitingConnectorCount() const
{
	return ExitingConnectorCount;
}

void OperatorAssign::incrementExitingConnectorCount()
{
	ExitingConnectorCount++;
}


Point OperatorAssign::getRightLoopInlet() const
{
	return RightLoopInlet;
}

void OperatorAssign::DecrementEnteringConnectorCount()
{
	EnteringConnectorCount--;
}

void OperatorAssign::DecrementExitingConnectorCount()
{
	ExitingConnectorCount--;
}

int OperatorAssign::Simulate(std::string varNames[], int& varCount, double varValues[], bool varDeclared[], bool varInitialized[], std::string& outputAccum, Input* pIn, Output* pOut) {
    // find index of name in varNames
    auto findIdx = [&](const std::string &name) -> int {
        for (int i = 0; i < varCount; ++i) if (varNames[i] == name) return i;
        return -1;
    };

    // resolve a token that may be a literal or a variable
    auto resolve_val = [&](const std::string &s, double &out) -> bool {
        try { out = stod(s); return true; } catch(...) { }
        int idx = findIdx(s);
        if (idx == -1 || !varInitialized[idx]) return false;
        out = varValues[idx];
        return true;
    };

    int li = findIdx(LHS);
    if (li == -1 || !varDeclared[li]) { pOut->PrintMessage((std::string("Run Error: variable '") + LHS + "' used before declaration").c_str()); return 0; }
    double a=0,b=0; bool aok=false,bok=false;
    aok = resolve_val(RHS1,a);
    bok = resolve_val(RHS2,b);
    if (!aok || !bok) { pOut->PrintMessage("Run Error: operand not ready"); return 0; }
    double res = 0;
    if (RHS_op == "+") res = a + b;
    else if (RHS_op == "-") res = a - b;
    else if (RHS_op == "*") res = a * b;
    else if (RHS_op == "/") { if (b == 0) { pOut->PrintMessage("Run Error: division by zero"); return 0; } res = a / b; }
    varValues[li] = res; varInitialized[li] = true;
    return 0;
}