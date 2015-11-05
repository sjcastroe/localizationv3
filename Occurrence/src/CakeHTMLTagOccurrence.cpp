/*
 * CakeHTMLTagOccurrence.cpp
 *
 *  Created on: Oct 16, 2015
 *      Author: root
 */

#include "CakeHTMLTagOccurrence.h"
#include <iostream>

namespace scastroOccurrence
{

	CakeHTMLTagOccurrence::CakeHTMLTagOccurrence()
	{
		occurrenceType = "Cake HTML Tag";
	}

	void CakeHTMLTagOccurrence::handle(std::string& data)
	{
		//std::cout << "LINE: " << line << std::endl;
		int newLineOffset = line.length() - data.length();

		StrRange argRange = findArg(line, occurrenceType, 2);

		if (argRange.beg == -2)
			inAlert = false;
		else
		{
			//std::cout << "ARGRANGE: " << argRange.beg << "    " << argRange.end << std::endl;

			std::string firstArg = line.substr(argRange.beg, argRange.end - argRange.beg);

			argRange = getArg(firstArg, argRange);

			if (argRange.end == -1)
				inAlert = true;
			else
			{
				argRange.beg -= newLineOffset;
				argRange.end -= newLineOffset;

				std::string dataMid = data.substr(argRange.beg, argRange.end - argRange.beg);
				if (!scastroWildcard::Wildcard::eval("*null*", dataMid.c_str()))
				{
					std::string dataBeg = data.substr(0, argRange.beg);
					std::string dataEnd = data.substr(argRange.end);

					data = dataBeg + "__(" + dataMid + ", true)" + dataEnd;
				}

				inAlert = false;
			}
		}

	}

	bool CakeHTMLTagOccurrence::isFound()
	{
		if (line.find("$this->Html->tag") != -1)
			return true;
		else
			return false;
	}

	void CakeHTMLTagOccurrence::feed(std::string li)
	{
		if (inAlert)
			line += li;
		else
			line = li;
	}

	//line is function to traverse as a string, argRange is the starting argument range (if line was an argument of another function)
	StrRange CakeHTMLTagOccurrence::getArg(const std::string line, StrRange& argRange)
	{
		int funcNameEnd = -1;
		for (unsigned int i = 0; i < line.length(); i++)
		{
			if (line[i] == '(')
			{
				funcNameEnd = i;
				break;
			}
		}
		if (funcNameEnd == -1)
		{
			return argRange;
		}

		std::string funcName = line.substr(0, funcNameEnd);
		//std::cout << funcName << std::endl;

		StrRange nextArgRange = findArg(line, funcName, 1);
		if (nextArgRange.end != -1)
		{
			argRange.end = argRange.beg + nextArgRange.end;
			argRange.beg += nextArgRange.beg;

			std::string nextArg = line.substr(nextArgRange.beg, nextArgRange.end - nextArgRange.beg);
			//std::cout << "inside getArg: " << nextArg << std::endl;

			return getArg(nextArg, argRange);
		}
		else
			return nextArgRange;
	}

	//We have a line -> find function occurrence, find its nth argument, return beg and end position
	//return -1 -> if we haven't found the target data BUT the function HAS NOT exited
	//return -2 -> if we haven't found the target data AND the function HAS exited
	StrRange CakeHTMLTagOccurrence::findArg(const std::string& line, std::string occurrence, int arg)
	{
		if (!(arg >= 1))
		{
			std::string eMessage = "findArg Error: Invalid argument input. Select a number greater than or equal to one corresponding with the function to select.";
			std::runtime_error badArgNo(eMessage);
			throw badArgNo;
		}

		size_t argsBeg = line.find(occurrence);

		if (argsBeg == -1)
		{
			std::string eMessage = "findArg Error: The occurrence was not found in the line string.";
			std::runtime_error NoOccur(eMessage);
			throw NoOccur;
		}

		StrRange argument;//return value

		argsBeg = argsBeg + occurrence.length() + 1;

		std::string args = line.substr(argsBeg);

		int bracketLevel = 0;
		int beg = 0;//first char of argument
		int end = 0;//char after last char of argument

		//check that the function takes arguments
		int argsSize = args.length();
		for (unsigned int j = 0; j < argsSize; j++)
		{
			if (args[j] == '(')
				bracketLevel++;
			if (args[j] == ')')
				bracketLevel--;

			if (args[j] != ' ' && bracketLevel == 0)
				break;
			if (bracketLevel < 0)
			{
				argument.beg = -2;
				argument.end = -2;
				return argument;
			}
		}

		for (unsigned int i = 0; i < arg; i++)
		{
			for (unsigned int j = 0; j < args.length(); j++)
			{
				if (args[j] == '(')
					bracketLevel++;
				if (args[j] == ')')
					bracketLevel--;

				//check if we exited the function
				if (bracketLevel < 0 && i < arg - 1)
				{
					argument.beg = -2;
					argument.end = -2;
					return argument;
					/*
					std::string eMessage = "findArg Error: Invalid argument number. The function occurrence accepts less arguments than requested.";
					std::runtime_error badArgNo(eMessage);
					throw badArgNo;
					*/
				}

				if ((args[j] == ',' && bracketLevel == 0 && j != 0) || (bracketLevel < 0 && i == arg - 1))
				{
					args = args.substr(j);

					if (i > 0)
						beg = end + 1;
					end = end + j;
					break;
				}

				//if we've read the whole line and haven't found what we wanted, but the function hasn't exited -> we have to read next line
				if (j == args.length() - 1)
				{
					argument.beg = argsBeg + beg;
					argument.end = -1;
					return argument;
				}
			}
		}


		argument.beg = argsBeg + beg;
		argument.end = argsBeg + end;

		return argument;
	}

}


