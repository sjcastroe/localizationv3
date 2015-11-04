/*
 * WildcardOccurrence.cpp
 *
 *  Created on: Oct 1, 2015
 *      Author: root
 */

#include <string>
#include "HTMLTagOccurrence.h"

namespace scastroOccurrence
{

	HTMLTagOccurrence::HTMLTagOccurrence()
	{
		occurrenceType = "HTML Tag";
		range.beg = -1;
		range.end = -1;
	}

	void HTMLTagOccurrence::handle(std::string& data)
	{
		std::string dataBeg = data.substr(0, range.beg);
		std::string dataMid = data.substr(range.beg, range.end - range.beg);
		std::string dataEnd = data.substr(range.end);

		data = dataBeg + "<?php __(" + dataMid + ")?>" + dataEnd;
	}

	bool HTMLTagOccurrence::isFound()
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (deltaTagLevel == 1 && line[i] == '>')
			{
				range.beg = i + 1;
			}
			if (line[i] == '<' && line[i + 1] != '/')//if beg tag (will also count inline tags)
			{
				tagLevel += 1;
				deltaTagLevel = 1;
			}
			if (line[i] == '/' && line[i + 1] == '>')// if inline tag
			{
				tagLevel -= 1;
				if (tagLevel < 0)
				{
					std::string eMessage = "HTMLTagOccurrence::isFound() ERROR: Negative tag level at line: " + line;
					std::runtime_error negTagLvl(eMessage);
					throw negTagLvl;
				}
				deltaTagLevel = -1;
			}
			if (line[i] == '<' && line[i + 1] == '/' && deltaTagLevel == 1 )//if ending tag and relative maximum
			{
				tagLevel -= 1;
				if (tagLevel < 0)
				{
					std::string eMessage = "HTMLTagOccurrence::isFound() ERROR: Negative tag level at line: " + line;
					std::runtime_error negTagLvl(eMessage);
					throw negTagLvl;
				}
				deltaTagLevel = -1;
				range.end = i;
				return true;
			}

		}
		range.beg = -1;
		return false;
	}

	void HTMLTagOccurrence::feed(std::string li)
	{
		line = li;
	}


}


