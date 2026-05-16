#include "HelperFn.h"
#include <cctype>

bool IsValue(string input)
{
	// checks if the input string is a double value
	// return true if it's double value, false otherwise

	// Double values can be: 12.5, -12.5, -23, -23. , -23.0 Åcetc.

	//TODO: complete this function

	if (input.length() == 0)	// if the user enters nothing
	{
		return false;
	}

	if (input.length() == 1 && input == "-")	// if the user enters only the negative sign without a number 
	{
		return false;
	}

	for (int i = 0; i < input.length(); i++)
	{
		if (isdigit(input[i]) || input[i] == '-' || input[i] == '.') {
			continue;
		}
		else {
			return false;
		}
	}

	return true;
}

bool IsVariable(string input)
{
	// checks if the input string is a variable name
	// return true if it can be a variable name, false otherwise

	// Variable names must start with an alphabetic letter (small or capital) or an underscore (_). 
	// After the first initial letter, variable names can contain letters, numbers and underscores.  
	// No spaces or special characters, however, are allowed.

	//TODO: complete this function

	if (input.length() == 0)	// if the user enters nothing
	{
		return false;
	}

	for (int i = 0; i < input.length(); i++)
	{
		if (i == 0)
		{
			if (isalpha(input[i]) || input[i] == '_')
				continue;
			else
				return false;
		}
		else
		{
			if (isalnum(input[i]) || input[i] == '_')
				continue;
			else
				return false;
		}
	}

	return true;
}

OpType ValueOrVariable(string input)
{
	// checks if the input string is a double value or a variable name
	// chand returns enum "OpType" (the enum is declared in the .h)

	//TODO: complete this function

	if (IsValue(input))
		return VALUE_OP;
	else if (IsVariable(input))
		return VARIABLE_OP;
	else
		return INVALID_OP;

}