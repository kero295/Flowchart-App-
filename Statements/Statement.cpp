#include "Statement.h"

int Statement::Count = 0; //Initialize the static data member ID

Statement::Statement()	
{ 
	//TODO: set the ID with a unique value
	
	ID = ++Count;
	Text = "";
	Selected = false;	
	EnteringConnectorCount = 0;
	ExitingConnectorCount = 0;
}


void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

void Statement::ResetCount()
{
	Count = 0;
}
