#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "AddVariableAssign.h"
#include "AddDeclareVariable.h"
#include "AddOperatorAssign.h"
#include "AddConditional.h"
#include "AddRead.h"
#include "AddStart.h"
#include "AddEnd.h"
#include "AddWrite.h"
#include "AddConnector.h"
#include "Select.h"
#include "Edit.h"
#include "Copy.h"
#include "Cut.h"
#include "Paste.h"
#include "Delete.h"
#include "Save.h"
#include "Switch.h"
#include "Load.h"
#include "Validate.h"
#include "RunAction.h"
#include "GenerateCppCode.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "GUI\UI_Info.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

#include "Start.h"
#include "End.h"
#include "Conditional.h"
#include "Read.h"
#include "Write.h"
#include "ValueAssign.h"
#include "VarAssign.h"
#include "DeclareVariable.h"

using namespace std;

// constructor: initialize ui, counters and lists
ApplicationManager::ApplicationManager()
{
	// create input and output handlers
	pOut = new Output;
	pIn = pOut->CreateInput();

	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;    // no statement selected yet
	pClipboard = NULL;
	pSelectedConn = NULL;

	// initialize statement and connector arrays
	for (int i = 0; i < MaxCount; i++)
	{
		StatList[i] = NULL;
		ConnList[i] = NULL;
	}
}


//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < StatCount; i++)
		delete StatList[i];
	for (int i = 0; i < StatCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;

}


void ApplicationManager::GenerateCode(const string &filename)
{
	if (!ValidateChart()) return;

	// find the start statement
	Statement* startStmt = NULL;
	for (int i = 0; i < StatCount; i++) if (dynamic_cast<Start*>(StatList[i])) startStmt = StatList[i];
	if (!startStmt) { pOut->PrintMessage("Generate Error: No start statement."); return; }

	ofstream ofs(filename.c_str());
	if (!ofs.is_open()) { pOut->PrintMessage("Generate Error: cannot open output file."); return; }

	// always exist in the file
	ofs << "#include <iostream>\n";
	ofs << "#include <string>\n";
	ofs << "using namespace std;\n\n";
	ofs << "int main() {\n";

	// declare variables found in declare-variable statements
	for (int i = 0; i < StatCount; i++)
	{
		DeclareVariable* dv = dynamic_cast<DeclareVariable*>(StatList[i]);
		if (dv)
		{
			string txt = dv->GetText(); // example: "double x"
			istringstream iss(txt); string t, var; iss >> t >> var;
			if (!var.empty()) ofs << "    double " << var << " = 0;\n";
		}
	}
	ofs << "\n";

	// traverse the flowchart and emit code
	bool visited[MaxCount];
	memset(visited, 0, sizeof(visited));
	GenerateCodeFrom(startStmt, ofs, visited);

	ofs << "    return 0;\n";
	ofs << "}\n";
	ofs.close();
	pOut->PrintMessage("Code generation finished.");
}

ActionType ApplicationManager::GetUserAction() const
{
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////
// creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	// according to action type, create the corresponding action object
	switch (ActType)
	{
	case ADD_VALUE_ASSIGN:
		pAct = new AddValueAssign(this);
		break;

	case ADD_CONDITION:
		pAct = new AddConditional(this);
		break;

	case ADD_VAR_ASSIGN:
		pAct = new AddVarAssign(this);
		break;

	case ADD_START:
		pAct = new AddStart(this);
		break;

	case ADD_END:
		pAct = new AddEnd(this);
		break;

	case ADD_DECLARE_VARIABLE:
		pAct = new AddDeclareVariable(this);
		break;

	case ADD_OPER_ASSIGN:
		pAct = new AddOperatorAssign(this);
		break;

	case ADD_READ:
		pAct = new AddRead(this);
		break;

	case ADD_WRITE:
		pAct = new AddWrite(this);
		break;

	case ADD_CONNECTOR:
		pAct = new AddConnector(this);
		break;

	case SELECT:
		pAct = new Select(this);
		break;

	case EDIT_STAT:
		pAct = new Edit(this);
		break;

	case COPY:
		pAct = new Copy(this);
		break;

	case CUT:
		pAct = new Cut(this);
		break;

	case PASTE:
		pAct = new Paste(this);
		break;

	case SAVE:
		pAct = new Save(this);
		break;

	case LOAD:
		pAct = new Load(this);
		break;

	case SWITCH_SIM_MODE:
		pAct = new Switch(this);
		break;

	case DEL:
		pAct = new Delete(this);
		break;

	case SWITCH_DSN_MODE:
		pAct = new Switch(this);
		break;

	case VALIDATE:
		
		pAct = new Validate(this);
		break;

	case RUN:

		pAct = new RunAction(this);
		break;

	case GENERATE_CODE:

		pAct = new GenerateCppCode(this);
		break;

	case EXIT:
		// create exit action here if needed
		break;

	case STATUS:
		return;
	}

	// execute the created action
	if (pAct != NULL)
	{
		pAct->Execute(); // execute
		delete pAct;    // action no longer needed
	}
}


//==================================================================================//
//                        statements management functions                            //
//==================================================================================//


// add a statement to the list of statements
void ApplicationManager::AddStatement(Statement* pStat)
{
	if (StatCount < MaxCount)
		StatList[StatCount++] = pStat;

}

////////////////////////////////////////////////////////////////////////////////////
Statement* ApplicationManager::GetStatement(Point P) const
{
	// if point P is inside any statement return it, otherwise return null
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->IsClickInside(P))
		{
			return StatList[i];
		}
	}

	return NULL;
}
void ApplicationManager::AddConn(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}
Connector* ApplicationManager::GetConnector(Point P) const
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->IsInsideConnector(P))
		{
			return ConnList[i];
		}
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
// returns the selected statement
Statement* ApplicationManager::GetSelectedStatement() const
{
	return pSelectedStat;
}

////////////////////////////////////////////////////////////////////////////////////
// set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement* pStat)
{
	pSelectedStat = pStat;
}

////////////////////////////////////////////////////////////////////////////////////
// returns the clipboard
Statement* ApplicationManager::GetClipboard() const
{
	return pClipboard;
}

////////////////////////////////////////////////////////////////////////////////////
// set the clipboard
void ApplicationManager::SetClipboard(Statement* pStat)
{
	pClipboard = pStat;
}

Connector* ApplicationManager::GetSelectedConnector() const
{
	return pSelectedConn;
}

void ApplicationManager::SetSelectedConnector(Connector* pConn)
{
	pSelectedConn = pConn;
}


////////////////////////////////////////////////////////////////////////////////////
//                            interface management functions                        //
//==================================================================================//


// draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	// draw all statements
	for (int i = 0; i < StatCount; i++)
		StatList[i]->Draw(pOut);

	// draw all connections
	for (int i = 0; i < ConnCount; i++)
		ConnList[i]->Draw(pOut);

}

void ApplicationManager::DeleteConnector(Connector* selected)
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (selected == ConnList[i])
		{
			for (int j = i; j < ConnCount - 1; j++)
			{
				ConnList[j] = ConnList[j + 1];
			}

			ConnList[ConnCount - 1] = NULL;
			ConnCount--;

			break;
		}
	}
}

void ApplicationManager::DeleteStatement(Statement* selected)
{
	for (int i = 0; i < StatCount; i++)
	{
		if (selected == StatList[i])
		{

			if (dynamic_cast<Start*>(selected))
			{
				Connector* DeletedConnector = GetConnector(selected->getOutlet());

				if (DeletedConnector)
				{
					DeleteConnector(DeletedConnector);
				}

			}
			else if (dynamic_cast<End*>(selected))
			{
				Connector* DeletedConnector = GetConnector(selected->getInlet());
				if (DeletedConnector)
				{
					DeletedConnector->getSrcStat()->DecrementExitingConnectorCount();
					DeleteConnector(DeletedConnector);
				}
			}
			else if (dynamic_cast<Conditional*>(selected))
			{
				Connector* DeletedConnector1 = GetConnector(selected->getInlet());
				Connector* DeletedConnector2 = GetConnector(((Conditional*)selected)->getRightOutlet());
				Connector* DeletedConnector3 = GetConnector(selected->getOutlet());

				if (DeletedConnector1)
				{
					DeletedConnector1->getSrcStat()->DecrementExitingConnectorCount();
					DeleteConnector(DeletedConnector1);
				}

				if (DeletedConnector2)
				{
					DeleteConnector(DeletedConnector2);
				}

				if (DeletedConnector3)
				{
					DeleteConnector(DeletedConnector3);
				}

			}
			else
			{
				Connector* DeletedConnector1 = GetConnector(selected->getInlet());
				Connector* DeletedConnector2 = GetConnector(selected->getOutlet());

				if (DeletedConnector1)
				{
					DeletedConnector1->getSrcStat()->DecrementExitingConnectorCount();
					DeleteConnector(DeletedConnector1);
				}

				if (DeletedConnector2)
				{
					DeletedConnector2->getSrcStat()->DecrementExitingConnectorCount();
					DeleteConnector(DeletedConnector2);

				}
			}


			for (int j = i; j < StatCount - 1; j++)
			{
				StatList[j] = StatList[j + 1];
			}

			StatList[StatCount - 1] = NULL;
			StatCount--;

			UpdateInterface();
			return;
		}
	}
}

bool ApplicationManager::IsStatementOverlapping(Point P) const
{
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->IsClickInside(P))
		{
			pOut->PrintMessage("Error: Overlapping Statements");
			return true;
		}
	}
	return false;
}

void ApplicationManager::SaveFile(string filename)
{

	ofstream file(filename);

	if (!file.is_open()) {
		pOut->PrintMessage("Error opening file!");
		return;
	}

	file << StatCount << endl;

	for (int i = 0; i < StatCount; i++)
	{
		StatList[i]->Save(file);
	}

	file << ConnCount << endl;

	for (int i = 0; i < ConnCount; i++)
	{
		ConnList[i]->Save(file);
	}
}

void ApplicationManager::ClearFlowChart()
{
	for (int i = 0; i < StatCount; i++)
	{
		delete StatList[i];
		StatList[i] = nullptr;
	}
	StatCount = 0;

	for (int i = 0; i < ConnCount; i++)
	{
		delete ConnList[i];
		ConnList[i] = nullptr;
	}
	ConnCount = 0;

	pSelectedStat = nullptr;
	pSelectedConn = nullptr;

	Statement::ResetCount();   
	pOut->ClearDrawArea();
}


//==================================================================================//
//                            simulation functions                                  //
//==================================================================================//



bool ApplicationManager::ValidateChart()
{
	// basic checks: exactly one start and one end
	int startCnt = 0, endCnt = 0;
	Statement* startStmt = NULL;
	for (int i = 0; i < StatCount; i++)
	{
		if (dynamic_cast<Start*>(StatList[i])) { startCnt++; startStmt = StatList[i]; }
		if (dynamic_cast<End*>(StatList[i])) { endCnt++; }
	}

	if (startCnt != 1)
	{
		pOut->PrintMessage("Validation Error: Flowchart must have exactly one Start statement.");
		return false;
	}
	if (endCnt != 1)
	{
		pOut->PrintMessage("Validation Error: Flowchart must have exactly one End statement.");
		return false;
	}

	
	int outCount[MaxCount];
	int inCount[MaxCount];
	for (int i = 0; i < StatCount; i++) { outCount[i] = 0; inCount[i] = 0; }
	for (int i = 0; i < ConnCount; i++)
	{
		Statement* s = ConnList[i]->getSrcStat();
		Statement* d = ConnList[i]->getDstStat();
		int srcIdx = -1, dstIdx = -1;
		for (int k = 0; k < StatCount; k++) {
			if (StatList[k] == s) srcIdx = k;
			if (StatList[k] == d) dstIdx = k;
		}
		if (srcIdx != -1) outCount[srcIdx]++;
		if (dstIdx != -1) inCount[dstIdx]++;
	}

	int startIdx = -1;
	for (int k = 0; k < StatCount; k++) if (StatList[k] == startStmt) startIdx = k;
	if (startIdx != -1 && inCount[startIdx] != 0)
	{
		pOut->PrintMessage("Validation Error: Start statement must not have incoming connectors.");
		return false;
	}

	// find end statement
	Statement* endStmt = NULL;
	int endIdx = -1;
	for (int i = 0; i < StatCount; i++) if (dynamic_cast<End*>(StatList[i])) { endStmt = StatList[i]; endIdx = i; }
	if (endStmt && endIdx != -1 && outCount[endIdx] != 0)
	{
		pOut->PrintMessage("Validation Error: End statement must not have outgoing connectors.");
		return false;
	}

	// check outgoing constraints per type
	for (int i = 0; i < StatCount; i++)
	{
		Statement* s = StatList[i];
		int oc = outCount[i];
		if (dynamic_cast<Conditional*>(s))
		{
			if (oc != 2)
			{
				pOut->PrintMessage("Validation Error: Conditional statement must have two outgoing connectors.");
				return false;
			}
		}
		else if (dynamic_cast<Start*>(s))
		{
			if (oc != 1)
			{
				pOut->PrintMessage("Validation Error: Start statement must have exactly one outgoing connector.");
				return false;
			}
		}
		else if (dynamic_cast<End*>(s))
		{
			// already checked
		}
		else
		{
			if (oc != 1)
			{
				pOut->PrintMessage("Validation Error: Every non-conditional, non-end statement must have exactly one outgoing connector.");
				return false;
			}
		}
	}

	// check internal counters match actual connector counts
	for (int i = 0; i < StatCount; i++)
	{
		Statement* s = StatList[i];
		if (dynamic_cast<Start*>(s) || dynamic_cast<End*>(s))
		{
			// skip start/end as they have no counters to check
			continue;
		}
		if (dynamic_cast<Conditional*>(s))
		{
			// skip conditional as it has no internal counters to check
			continue;
		}
		if (outCount[i] != s->getExitingConnectorCount())
		{
			pOut->PrintMessage("Validation Error: Outgoing connector count mismatch detected.");
			return false;
		}
		if (inCount[i] != s->getEnteringConnectorCount())
		{
			pOut->PrintMessage("Validation Error: Incoming connector count mismatch detected.");
			return false;
		}
	}

	// connectivity: bfs from start following connectors
	Statement* visitedList[MaxCount];
	int visitedCount = 0;
	bool visited[MaxCount];
	for (int i = 0; i < StatCount; i++) visited[i] = false;
	Statement* q[MaxCount];
	int qFront = 0, qRear = 0;
	q[qRear++] = startStmt;
	visited[startIdx] = true;
	while (qFront < qRear)
	{
		Statement* cur = q[qFront++];
		visitedList[visitedCount++] = cur;
		// iterate connectors to find outgoing
		for (int i = 0; i < ConnCount; i++)
		{
			if (ConnList[i]->getSrcStat() == cur)
			{
				Statement* dst = ConnList[i]->getDstStat();
				int dstIdx = -1;
				for (int k = 0; k < StatCount; k++) if (StatList[k] == dst) dstIdx = k;
				if (dstIdx != -1 && !visited[dstIdx]) { visited[dstIdx] = true; q[qRear++] = dst; }
			}
		}
	}

	if (visitedCount != StatCount)
	{
		pOut->PrintMessage("Validation Error: Flowchart is not fully connected (some statements unreachable from Start).");
		return false;
	}

	pOut->PrintMessage("Validation: OK");
	return true;
}

// run the flowchart by traversing from start and executing statements
void ApplicationManager::RunChart()
{
	if (!ValidateChart()) return;

	// find start
	Statement* startStmt = NULL;
	for (int i = 0; i < StatCount; i++) if (dynamic_cast<Start*>(StatList[i])) startStmt = StatList[i];
	if (!startStmt) { pOut->PrintMessage("Run Error: No start statement."); return; }

	// prepare variable storage arrays
	string varNames[100];
	int varCount = 0;
	double varValues[100];
	bool varDeclared[100];
	bool varInitialized[100];
	for (int i = 0; i < 100; ++i) { varDeclared[i] = false; varInitialized[i] = false; }

	Statement* cur = startStmt;
	string outputAccum = "";

	int safety = 0; // prevent infinite loops
	while (cur != nullptr && safety++ < 1000)
	{
		int branch = cur->Simulate(varNames, varCount, varValues, varDeclared, varInitialized, outputAccum, pIn, pOut);
		// move to the next statement according to branch value

		if (branch == -1)
		{
			// simulation error occurred
			pOut->PrintMessage("Run Error: Double declaration.");
			return;

		}

		if (branch == 0) {
			// follow first outgoing connector
			Connector* next = NULL;
			for (int i = 0; i < ConnCount; i++) if (ConnList[i]->getSrcStat() == cur) { next = ConnList[i]; break; }
			if (next) cur = next->getDstStat(); else cur = NULL;
		} else if (branch == 1) {
			// right branch for conditional
			Conditional* c = dynamic_cast<Conditional*>(cur);
			if (c) {
				Connector* rightConn = NULL;
				for (int i = 0; i < ConnCount; i++) {
					if (ConnList[i]->getSrcStat() == cur) {
						Statement* dst = ConnList[i]->getDstStat();
						if (dst->getInlet().x > c->getRightOutlet().x) rightConn = ConnList[i];
					}
				}
				if (rightConn) cur = rightConn->getDstStat(); else cur = NULL;
			}
		} else if (branch == 2) {
			// left branch
			Conditional* c = dynamic_cast<Conditional*>(cur);
			if (c) {
				Connector* leftConn = NULL;
				for (int i = 0; i < ConnCount; i++) {
					if (ConnList[i]->getSrcStat() == cur) {
						Statement* dst = ConnList[i]->getDstStat();
						if (dst->getInlet().x <= c->getRightOutlet().x) leftConn = ConnList[i];
					}
				}
				if (leftConn) cur = leftConn->getDstStat(); else cur = NULL;
			}
		}
	}

	if (safety >= 1000) { pOut->PrintMessage("Run Error: possible infinite loop detected."); return; }

	// display accumulated outputs in the output panel
	pOut->ClearOutputBar();
	istringstream iss(outputAccum);
	string line;
	int y = UI.ToolBarHeight + 10;
	while (getline(iss, line)) {
		pOut->DrawString(UI.DrawingAreaWidth + 10, y, line);
		y += 20;
	}

	//DebugRun();
}

// debug run: step-by-step execution showing variables after each statement
void ApplicationManager::DebugRun()
{
	if (!ValidateChart()) return;

	// find start
	Statement* startStmt = NULL;
	for (int i = 0; i < StatCount; i++) if (dynamic_cast<Start*>(StatList[i])) startStmt = StatList[i];
	if (!startStmt) { pOut->PrintMessage("Debug Error: No start statement."); return; }

	// prepare variable storage arrays
	string varNames[100];
	int varCount = 0;
	double varValues[100];
	bool varDeclared[100];
	bool varInitialized[100];
	for (int i = 0; i < 100; ++i) { varDeclared[i] = false; varInitialized[i] = false; }

	string outputAccum = "";

	Statement* cur = startStmt;

	int safety = 0;
	Point dummy;
	while (cur != nullptr && safety++ < 1000)
	{
		// show current statement and variables
		string status = string("[DEBUG] At: ") + cur->GetText() + " || ";
		for (int i = 0; i < varCount; i++)
		{
			status += varNames[i] + "=";
			if (varInitialized[i]) status += to_string(varValues[i]); else status += "<uninit>";
			status += " ";
		}
		pOut->PrintMessage(status.c_str());

		// wait for user click to proceed
		pIn->GetPointClicked(dummy);

		// simulate
		int branch = 0;
		if (dynamic_cast<Read*>(cur)) {
			string text = cur->GetText(); istringstream issr(text); string tt, var; issr >> tt >> var;
			if (!var.empty()) {
				int idx = -1;
				for (int i = 0; i < varCount; ++i) if (varNames[i] == var) { idx = i; break; }
				if (idx == -1 || !varDeclared[idx]) { pOut->PrintMessage((string("Debug Error: variable '") + var + "' used before declaration").c_str()); return; }

			}
		} else {
			branch = cur->Simulate(varNames, varCount, varValues, varDeclared, varInitialized, outputAccum, pIn, pOut);
		}

		if (branch == 0) {
			Connector* next = NULL;
			for (int i = 0; i < ConnCount; i++) if (ConnList[i]->getSrcStat() == cur) { next = ConnList[i]; break; }
			if (next) cur = next->getDstStat(); else cur = NULL;
		} else if (branch == 1) {
			// right branch for conditional
			Conditional* c = dynamic_cast<Conditional*>(cur);
			if (c) {
				Connector* rightConn = NULL;
				for (int i = 0; i < ConnCount; i++) {
					if (ConnList[i]->getSrcStat() == cur) {
						Statement* dst = ConnList[i]->getDstStat();
						if (dst->getInlet().x > c->getRightOutlet().x) rightConn = ConnList[i];
					}
				}
				if (rightConn) cur = rightConn->getDstStat(); else cur = NULL;
			}
		} else if (branch == 2) {
			// left branch
			Conditional* c = dynamic_cast<Conditional*>(cur);
			if (c) {
				Connector* leftConn = NULL;
				for (int i = 0; i < ConnCount; i++) {
					if (ConnList[i]->getSrcStat() == cur) {
						Statement* dst = ConnList[i]->getDstStat();
						if (dst->getInlet().x <= c->getRightOutlet().x) leftConn = ConnList[i];
					}
				}
				if (leftConn) cur = leftConn->getDstStat(); else cur = NULL;
			}
		}
	}

	if (safety >= 1000) pOut->PrintMessage("Debug Error: possible infinite loop detected.");
	else pOut->PrintMessage("Debug run finished.");
}


void ApplicationManager::GenerateCodeFrom(Statement* s, ofstream& ofs, bool visited[])
{
    if (visited[s->getID()]) return;
    visited[s->getID()] = true;

    if (dynamic_cast<ValueAssign*>(s) || dynamic_cast<VarAssign*>(s))
    {
        string text = s->GetText();
        ofs << "    " << text << ";\n";
    }
    else if (dynamic_cast<Read*>(s))
    {
        string text = s->GetText(); istringstream iss(text); string t, var; iss >> t >> var;
        ofs << "    cin >> " << var << ";\n";
    }
    else if (dynamic_cast<Write*>(s))
    {
        string text = s->GetText(); istringstream iss(text); string t, var; iss >> t >> var;
        ofs << "    cout << " << var << " << endl;\n";
    }
    else if (dynamic_cast<OperatorAssign*>(s))
    {
        string text = s->GetText();
        ofs << "    " << text << ";\n";
    }
    else if (dynamic_cast<Conditional*>(s))
    {
        string text = s->GetText(); istringstream iss(text); string lhs, op, rhs; iss >> lhs >> op >> rhs;
        ofs << "    if (" << lhs << " " << op << " " << rhs << ") {\n";

        // find right dst
        Statement* rightDst = NULL;
        Conditional* c = (Conditional*)s;
        for (int j = 0; j < ConnCount; j++) if (ConnList[j]->getSrcStat() == s) {
            Statement* dst = ConnList[j]->getDstStat();
            if (dst->getInlet().x > c->getRightOutlet().x) rightDst = dst;
        }
        if (rightDst) GenerateCodeFrom(rightDst, ofs, visited);

        ofs << "    } else {\n";

        // find left dst
        Statement* leftDst = NULL;
        for (int j = 0; j < ConnCount; j++) if (ConnList[j]->getSrcStat() == s) {
            Statement* dst = ConnList[j]->getDstStat();
            if (dst->getInlet().x <= c->getRightOutlet().x) leftDst = dst;
        }
        if (leftDst) GenerateCodeFrom(leftDst, ofs, visited);

        ofs << "    }\n";
        return; // don't continue after conditional
    }
    else if (dynamic_cast<End*>(s))
    {
        ofs << "    return 0;\n";
    }

    // for non-conditional, continue to next
    Connector* next = NULL;
    for (int j = 0; j < ConnCount; j++) if (ConnList[j]->getSrcStat() == s) { next = ConnList[j]; break; }
    if (next) GenerateCodeFrom(next->getDstStat(), ofs, visited);
}