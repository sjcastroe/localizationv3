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
		std:: string dataBeg = line.substr(0, range.beg);
		std:: string dataEnd = line.substr(range.end);

		data = dataBeg + "__" + dataEnd;
	}

	bool I18nOccurrence::isFound()
	{
		std::string occurrence = "$this->I18n->i18n";
		range.beg = line.find(occurrence);
		if (range.beg != -1)
		{
			range.end = range.beg + occurrence.length();
			return true;
		}
		else
			return false;
	}

	void I18nOccurrence::feed(std::string li)
	{
		line = li;
	}

}


