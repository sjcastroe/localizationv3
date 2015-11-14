/*
 * WildcardOccurrence.cpp
 *
 *  Created on: Oct 1, 2015
 *      Author: root
 */

#include "HTMLTagOccurrence.h"

namespace scastroOccurrence
{

	HTMLTagOccurrence::HTMLTagOccurrence()
	{
		occurrenceType = "HTML Tag";
		range.beg = -1;
		range.end = -1;
		subTargetRange.beg = -1;
		subTargetRange.end = -1;
	}

	void HTMLTagOccurrence::handle(std::string& data)
	{
		do
		{
			this->feed(data);
			this->findSubRange();

			//if we're in a <script> tag, and a sub range does not exist DO NOT handle (otherwise we'd handle all JS code in the tag)
			if(!(inScriptTag && !subRangeExists))
			{
				int rangeLength = subTargetRange.end - subTargetRange.beg;
				//std::cout << subTargetRange.beg << "   " << subTargetRange.end << std::endl;

				if (rangeLength < 0)
				{
					std::string eMessage = "Invalid target range.";
					std::runtime_error invTarRng(eMessage);
					throw invTarRng;
				}
				else if (rangeLength > 0)
				{
					//std::cout << subTargetRange.beg << "   " << subTargetRange.end <<  std::endl;
					std::string dataMid = data.substr(subTargetRange.beg, rangeLength);

					if (dataMid.find_first_not_of(' ') != std::string::npos)
					{
						std::string dataBeg = data.substr(0, subTargetRange.beg);
						std::string dataEnd = data.substr(subTargetRange.end);

						//std::cout << data[subTargetRange.end] << std::endl;

						if (dataMid[0] == '"')
						{
							dataMid.erase(0, 1);
							dataMid.erase(dataMid.size() - 1, 1);
						}

						dataMid = "'" + dataMid + "'";

						if (inPHPTag)
							data = dataBeg + "' . __(" + dataMid + ", true) . '" + dataEnd;
						else if (inScriptTag && !inPHPTag)
							data = dataBeg + "<?php __(" + dataMid + ", true)?>" + dataEnd;
						else
						{
							//range.end += 12;//size of added strings <?php __()?>
							data = dataBeg + "<?php __(" + dataMid + ")?>" + dataEnd;
						}
						range.beg = data.length() - dataEnd.length();
						int lengthNoWrap = dataBeg.length() + dataMid.length() + dataEnd.length();
						range.end += (data.length() - lengthNoWrap);
					}
				}
			}
		} while (subRangeExists);
	}

	bool HTMLTagOccurrence::isFound()
	{
		int lineSize = line.size();

		//get rid of blank space in front of target data, return false is line is empty
		if(inTargetRange)
		{
			for (int i = 0; i < lineSize; i++)
			{
				//std::cout << line[i] << std:: endl;
				if (!isblank(line[i]))
				{
					range.beg = i;
					break;
				}
				if (i == lineSize - 1)
					return false;
			}
		}

		for (int i = 0; i < lineSize; i++)
		{
			if (inPHPTag && (line[i] == '<' && line[i + 1] == '?'))
			{
				std::string eMessage = "HTMLTagOccurrence::isFound(): PHP tag within PHP tag.";
				std::runtime_error phpInPhp(eMessage);
				throw phpInPhp;
			}
			if (line[i] == '<' && line[i + 1] == '?')
			{
				inAlert = false;
				inTargetRange = false;
				inPHPTag = true;
			}
			if (line[i] == '?' && line[i + 1] == '>')
				inPHPTag = false;

			if (line[i] == '<' && line[i + 1] == 's' && line[i + 2] == 'c')
			{
				//std::cout << "JS tag found" << std::endl;
				inScriptTag = true;
			}

			if (line[i] == '<' && line[i + 1] == '/' && line[i + 2] == 's' && line[i + 3] == 'c')
				inScriptTag = false;

			//START HERE
			//find starting tag that is not a php tag '<?php' or a javascript tag '<script'
			if (line[i] == '<' && line[i + 1] != '/' && line[i + 1] != '-' && line[i + 1] != '?')
			{
				//checks if tag is being echoed or if its a real html tag
				if (line[i - 1] == '\"')
					echoedTag = true;
				inBegTag = true;
				range.beg = -1;
				inAlert = false;
			}
			//the '-' accounts for instances where '->' is used (otherwise '->' would be read as an ending tag)
			if (inBegTag && line[i] == '>' && line[i - 1] != '-')
			{
				inBegTag = false;
				inAlert = true;
				//if the end of the tag is also the end of the line ex. <div>\n
				if (i == lineSize - 1)
					return false;
				else
				{
					//accounts for tags being echoed vs real html tags (echoes tags will be in parentheses)
					if (line[i + 1] == '\"' && echoedTag)
						range.beg = i + 2;
					else
						range.beg = i + 1;
					echoedTag = false;
				}
			}

			//if in alert
			if (inAlert && i >= range.beg)
			{
				if (line[i] != ' ')
				{
					range.beg = i;
					inAlert = false;
					inTargetRange= true;
				}
			}

			if (inTargetRange)
			{
				//if we reach an ending tag
				if(line[i] == '<' && line[i + 1] == '/')
				{
					//std::cout << "test 1" <<  std::endl;
					inTargetRange = false;
					range.end = i;
					return true;
				}
				//if we reach the end of the line
				if(i == lineSize - 1)
				{
					range.end = i + 1;
					return true;
				}
			}
		}
		return false;
	}

	void HTMLTagOccurrence::feed(std::string li)
	{
		line = li;
	}

	void HTMLTagOccurrence::findSubRange()
	{
		bool targetFound = false;
		int newRangeBeg = -1;

		//std::cout << "Range String: " << line.substr(range.beg, range.end - range.beg) << std::endl;
		//std::cout << range.beg << "    " << range.end << std::endl;
		for(int i = range.beg; i < range.end; i++)
		{
			//Make sure parentheses are not in i18n function
			if (line[i] == '\"' && !targetFound) //&& line[i - 2] != '$')
			{
				newRangeBeg = i;
				targetFound = true;
				i++;
			}
			//std::cout << line[i] << "  ";
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
		subTargetRange.beg = range.beg;
		subTargetRange.end = range.end;

	}


}


