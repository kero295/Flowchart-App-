#include "Connector.h"
#include "Conditional.h"
#include <sstream>
using namespace std;

Connector::Connector(Statement* Src, Statement* Dst)	
//When a connector is created, it must have a source statement and a destination statement
//There are NO FREE connectors in the flowchart
{

	SrcStat = Src;
	DstStat = Dst;
	Selected = false;

	Start = Src->getOutlet();
	End = Dst->getInlet();

	if (dynamic_cast<Conditional*>(Src))
	{
		if (End.x > Start.x && End.y > Start.y)
		{
			Start = ((Conditional*)Src)->getRightOutlet();
			End = Dst->getInlet();
		}
		else if (End.x > Start.x && End.y < Start.y)
		{
			Start = ((Conditional*)Src)->getRightOutlet();
			End = Dst->getInlet();
		}
	}

	if (dynamic_cast<Conditional*>(Src) && Start.y > End.y)
	{
		Start = ((Conditional*)Src)->getRightOutlet();
		End = Dst->getRightLoopInlet();


	}

}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint() const
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint() const
{	return End;	}


bool Connector::IsInsideConnector(Point P) const
{
	int tolerance = 15;

	if ((P.x == Start.x && P.y == Start.y) || (P.x == End.x && P.y == End.y))
	{
		return true;
	}

	// for normal connector
	if (End.x >= Start.x) // right side
	{
		if (P.x > Start.x && P.x < End.x)
		{
			if (P.y < (Start.y + tolerance) && P.y > (Start.y - tolerance))
			{
				return true;
			}
		}
		else if (P.y > Start.y && P.y < End.y)
		{
			if (P.x < (End.x + tolerance) && P.x > (End.x - tolerance))
			{
				return true;
			}
		}
	}
	else if (Start.x > End.x) //left side
	{
		if (P.x < Start.x && P.x > End.x)
		{
			if (P.y < (Start.y + tolerance) && P.y > (Start.y - tolerance))
			{
				return true;
			}
		}
		else if (P.y > Start.y && P.y < End.y)
		{
			if (P.x < (End.x + tolerance) && P.x > (End.x - tolerance))
			{
				return true;
			}
		}
	}

	// for loop connectors
	if (End.x >= Start.x) // right side
	{
		if (P.x > Start.x && P.x < End.x + UI.ASSGN_WDTH / 2)
		{
			if ((P.y < (Start.y + tolerance) && P.y > (Start.y - tolerance)) || 
				(P.y < (End.y + tolerance) && P.y > (End.y - tolerance)))
			{
				return true;
			}
		}
		else if (P.y > End.y && P.y < Start.y)
		{
			if (P.x < (End.x + UI.ASSGN_WDTH / 2 + tolerance) && P.x > (End.x + UI.ASSGN_WDTH / 2 - tolerance))
			{
				return true;
			}
		}
	}
	else if (Start.x > End.x) //left side
	{
		if (P.x < Start.x && P.x > End.x - UI.ASSGN_WDTH / 2)
		{
			if ((P.y < (Start.y + tolerance) && P.y > (Start.y - tolerance)) || 
				(P.y < (End.y + tolerance) && P.y > (End.y - tolerance)))
			{
				return true;
			}
		}
		else if (P.y > End.y && P.y < Start.y)
		{
			if (P.x < (End.x - UI.ASSGN_WDTH / 2 + tolerance) && P.x > (End.x - UI.ASSGN_WDTH / 2 - tolerance))
			{
				return true;
			}
		}
	}
	
	return false;
}

void Connector::Draw(Output* pOut) const
{
	///TODO: Call Output to draw a connector from SrcStat to DstStat on the output window
	pOut->DrawConnector(Start, End, Selected);
}

void Connector::Save(ofstream& OutFile)
{
	if (dynamic_cast<Conditional*>(SrcStat) && DstStat->getInlet().y < dynamic_cast<Conditional*>(SrcStat)->getRightOutlet().y)
	{
		OutFile << SrcStat->getID() << " " << DstStat->getID() << ' ' << '1' << '\n';
	}
	else if (dynamic_cast<Conditional*>(SrcStat) && DstStat->getInlet().x > dynamic_cast<Conditional*>(SrcStat)->getRightOutlet().x)
	{
		OutFile << SrcStat->getID() << " " << DstStat->getID() << ' ' << '1' << '\n';
	}
	else if (dynamic_cast<Conditional*>(SrcStat) && DstStat->getInlet().x < dynamic_cast<Conditional*>(SrcStat)->getRightOutlet().x)
	{
		OutFile << SrcStat->getID() << " " << DstStat->getID() << ' ' << '2' << '\n';
	}
	else
	{
		OutFile << SrcStat->getID() << " " << DstStat->getID() << ' ' << '0' << '\n';
	}
}

void Connector::SetSelected(bool s)
{
	Selected = s;
}

bool Connector::IsSelected() const
{
	return Selected;
}