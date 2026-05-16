#include "Load.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include "Start.h"
#include "End.h"
#include "DeclareVariable.h"
#include "Connector.h"
#include "Conditional.h"
#include "ValueAssign.h"
#include "VarAssign.h"
#include "OperatorAssign.h"
#include "Read.h"
#include "Write.h"
#include "Conditional.h"
#include "DeclareVariable.h"


#include <fstream>
#include <string>
#include <sstream>
using namespace std;


Load::Load(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Load::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Enter file name to load:");
	FileName = pIn->GetString(pOut);
	pOut->ClearStatusBar();
}

bool Load::IsDrawnOnUI(Point P)
{
	return false;
}

void Load::Execute()
{
    ReadActionParameters();
    Output* pOut = pManager->GetOutput();
    ifstream InFile(FileName);

    if (!InFile.is_open())
    {
        pOut->PrintMessage("Error: Cannot open file!");
        return;
    }

    
    pManager->ClearFlowChart();

  
    int statCount;
    InFile >> statCount;
    Statement** TempStatList = new Statement * [statCount];

    for (int i = 0; i < statCount; i++)
        TempStatList[i] = nullptr;

    for (int i = 0; i < statCount; i++)
    {
        string type;
        InFile >> type;
        Statement* pStat = nullptr;

        if (type == "STRT")            pStat = new Start(Point(0, 0));
        else if (type == "END")        pStat = new End(Point(0, 0));
        else if (type == "DECLARE")    pStat = new DeclareVariable(Point(0, 0), "");
        else if (type == "VALUE_ASSIGN") pStat = new ValueAssign(Point(0, 0), "", 0);
        else if (type == "VAR_ASSIGN") pStat = new VarAssign(Point(0, 0), "", "");
        else if (type == "OP_ASSIGN")  pStat = new OperatorAssign(Point(0, 0), "", "", "", "");
        else if (type == "READ")       pStat = new Read(Point(0, 0), "");
        else if (type == "WRITE")      pStat = new Write(Point(0, 0), "");
        else if (type == "COND")       pStat = new Conditional(Point(0, 0), "", "", "");

        if (pStat)
        {
            pStat->Load(InFile);   
            pManager->AddStatement(pStat);
            TempStatList[i] = pStat;
        }
    }

   
    int connCount;
    InFile >> connCount;

    for (int i = 0; i < connCount; i++)
    {
        int srcID, dstID, flag;
        InFile >> srcID >> dstID >> flag;

        Statement* pSrc = nullptr;
        Statement* pDst = nullptr;

        for (int j = 0; j < statCount; j++)
        {
            if (TempStatList[j] == nullptr) continue;
            if (TempStatList[j]->getID() == srcID) pSrc = TempStatList[j];
            if (TempStatList[j]->getID() == dstID) pDst = TempStatList[j];
        }

        if (!pSrc || !pDst) continue;

        Connector* pConn = new Connector(pSrc, pDst);

     
        if (Conditional* pCond = dynamic_cast<Conditional*>(pSrc))
        {
            if (flag == 1) 
                pConn->setStartPoint(pCond->getRightOutlet());
            else if (flag == 2) 
                pConn->setStartPoint(pCond->getOutlet());
        }
        else
        {
            pConn->setStartPoint(pSrc->getOutlet());
        }

        if (flag == 1 && pConn->getEndPoint().y > pConn->getStartPoint().y)
        {
            pConn->setEndPoint(pDst->getInlet());
        }
        else if (flag == 1 && pConn->getEndPoint().y < pConn->getStartPoint().y)
        {
            pConn->setEndPoint(pDst->getRightLoopInlet());
        }
        else
        {
            pConn->setEndPoint(pDst->getInlet());
        }

        pManager->AddConn(pConn);
    }

    delete[] TempStatList;
    InFile.close();

    pManager->UpdateInterface();
    pOut->PrintMessage("Flowchart loaded successfully!");
}



