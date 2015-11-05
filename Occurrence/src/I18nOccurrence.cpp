/*
 * I18nOccurrence.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: root
 */

#include "I18nOccurrence.h"

namespace scastroOccurrence
{
	I18nOccurrence::I18nOccurrence()
	{
		occurrenceType = "I18n Wrapper";
	}

	void I18nOccurrence::handle(std::string& data)
	{
	}

	bool I18nOccurrence::isFound()
	{
		std::string occurrence = "$this->I18n->i18n";
		range.beg = line.find(occurrence);
		if (range.beg != -1)
		{
			range.beg += occurrence.length();
			int bracketLevel = 0;
			for (int i = range.beg; i < line; i++)
			{
				if (line[i] == '(')
					bracketLevel += 1;
				if(line[i] == ')')
					bracketLevel -= 1;
				if (line[i] == ')' && bracketLevel == 0)
				{
					range.end = i;
					return true;
				}
			}
			std::string eMessage = "I18nOccurrence::isFound(): End bracket of i18n() function not found.";
			std::runtime_error noEnd(eMessage);
			throw noEnd;

		}
		else
			return false;
	}

	void I18nOccurrence::feed(std::string li)
	{
		line = li;
	}

}


