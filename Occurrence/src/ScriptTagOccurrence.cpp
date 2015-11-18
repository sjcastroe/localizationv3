/*
 * ScriptTagOccurrence.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: root
 */

#include "ScriptTagOccurrence.h"

namespace scastroOccurrence
{
	ScriptTagOccurrence::ScriptTagOccurrence()
	{
		occurrenceType = "<script> Tag";
		range.beg = -1;
		range.end = -1;
		subTargetRange.beg = -1;
		subTargetRange.end = -1;
	}

	void ScriptTagOccurrence::handle(std::string& data)
	{
		do
		{
			this->feed(data);
			this->findSubRange();

			if(subRangeExists)
			{
				int rangeLength = subTargetRange.end - subTargetRange.beg;
				if (rangeLength < 0)
				{
					std::string eMessage = "Invalid target range.";
					std::runtime_error invTarRng(eMessage);
					throw invTarRng;
				}
				else if (rangeLength > 0)
				{
					std::string dataMid = data.substr(subTargetRange.beg, rangeLength);

					if (dataMid.find_first_not_of(' ') != std::string::npos)
					{
						std::string dataBeg = data.substr(0, subTargetRange.beg);
						std::string dataEnd = data.substr(subTargetRange.end);

						if (dataMid[0] == '"')
						{
							dataMid.erase(0, 1);
							dataMid.erase(dataMid.size() - 1, 1);
						}

						dataMid = "'" + dataMid + "'";

						data = dataBeg + "\"<?php __(" + dataMid + ");?>\"" + dataEnd;

						range.beg = data.length() - dataEnd.length();
						int lengthNoWrap = dataBeg.length() + dataMid.length() + dataEnd.length();
						range.end += (data.length() - lengthNoWrap);
					}
				}
			}
		} while (subRangeExists);
	}

	bool ScriptTagOccurrence::isFound()
	{
		int lineSize = line.size();

		if (inTargetRange)
			range.beg = 0;

		for (int i = 0; i < lineSize; i++)
		{
			if (line[i] == '<' && line[i + 1] == 's' && line[i + 2] == 'c')
				inBegTag = true;

			if (line[i] == '>' && inBegTag)
			{
				inTargetRange = true;
				range.beg = i + 1;
			}

			if (inTargetRange)
			{
				if (line[i] == '<' && line[i + 1] == '/' && line[i + 2] == 's' && line[i + 3] == 'c')
				{
					range.end = i;
					inTargetRange = false;
					return true;
				}

				if (i == lineSize - 1)
				{
					range.end = i + 1;
					return true;
				}
			}
		}
		return false;
	}

	void ScriptTagOccurrence::feed(std::string li)
	{
		line = li;
	}

	void ScriptTagOccurrence::findSubRange()
	{
		bool targetFound = false;
		int newRangeBeg = -1;

		for(int i = range.beg; i < range.end; i++)
		{
			//Make sure parentheses are not in i18n function
			if (line[i] == '\"' && !targetFound) //&& line[i - 2] != '$')
			{
				newRangeBeg = i;
				targetFound = true;
				i++;
			}
			if (line[i] == '\"' && targetFound)// && line[i + 2] != '.')
			{
				subTargetRange.beg = newRangeBeg;
				if (line[subTargetRange.beg - 3] != '8')//if range is argument of i18n function
				{
					subRangeExists = true;
					subTargetRange.end = i + 1;
					return;
				}
				targetFound = false;
			}
		}
		subRangeExists = false;
		//subTargetRange.beg = range.beg;
		//subTargetRange.end = range.end;

	}

}





