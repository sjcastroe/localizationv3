/*
 * InnerHTMLOccurrence.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: root
 */

#include "JQueryHTMLOccurrence.h"

namespace scastroOccurrence
{
/*
	JQueryHTMLOccurrence::JQueryHTMLOccurrence()
	{
		occurrenceType = "JavaScript InnerHTML";
	}

	void JQueryHTMLOccurrence::handle(std::string& data)
	{
		std::string occurrence = ".innerHTML =";
		while(true)
		{
			this->feed(data);
			range.beg = line.find(occurrence);
			if (range.beg == -1)
				break;

			inAlert = true;//flag to search for end of line ';'
			int lineSize = line.size();
			for (int i = range.beg; i < line.size(); i++)
			{
				if (line[i] == ';')
				{
					inAlert == false;
					range.end = i;
				}
				if (i == lineSize - 1)
				{

				}
			}

			std:: string dataBeg = line.substr(0, range.beg);
			std:: string dataEnd = line.substr(range.end);

			data = dataBeg + "__" + dataEnd;
		}
	}

	bool JQueryHTMLOccurrence::isFound()
	{
		std::string occurrence = ".innerHTML =";
		range.beg = line.find(occurrence);
		if (range.beg != -1)
			return true;
		else
			return false;
	}

	void JQueryHTMLOccurrence::feed(std::string li)
	{
		line = li;
	}
*/

}


