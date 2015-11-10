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
					{
						range.end += 10;//size of strings added __(,true)
						data = dataBeg + "__(" + dataMid + ", true)" + dataEnd;
					}
					else
					{
						range.end += 12;//size of added strings <?php __()?>
						data = dataBeg + "<?php __(" + dataMid + ")?>" + dataEnd;
					}
				}
			}
			//subTargetRange.beg = -1;
			//subTargetRange.end = -1;
		} while (subTargetRange.beg != -1);
	}

	bool HTMLTagOccurrence::isFound()
	{
		//std::cout << line << std::endl;
		int lineSize = line.size();

		//get rid of blank space in front of target data, return false is line is empty
		if(inTargetRange)
		{
			for (int i = 0; i < lineSize; i++)
			{
				//std::cout << line[i] << std:: endl;
				if(!isspace(line[i]))
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

			//START HERE
			if (line[i] == '<' && (line[i + 1] != '/' && line[i + 1] != '?'))
			{
				inBegTag = true;
				range.beg = -1;
				inAlert = false;
			}
			if (inBegTag && line[i] == '>')
			{
				inBegTag = false;
				inAlert = true;
				//if the end of the tag is also the end of the line ex. <div>\n
				if (i == lineSize - 1)
					return false;
				else
				{
					//accounts for tags being echoed vs real html tags (echoes tags will be in parentheses)
					if (line[i + 1] == '\"')
						range.beg = i + 2;
					else
						range.beg = i + 1;
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
				if(line[i] == '<' && line[i + 1] == '/')
				{
					//std::cout << "test 1" <<  std::endl;
					inTargetRange = false;
					range.end = i;
					return true;
				}
				if(i == lineSize - 1)
				{

					range.end = i + 1;
					//std::cout << "range.beg: " << range.beg <<  std::endl;
					//std::cout << "range.end: " << range.end <<  std::endl;
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

		//std::cout << range.beg << "    " << range.end << std::endl;
		for(int i = range.beg; i < range.end; i++)
		{
			//Make sure parentheses are not in i18n function
			if (line[i] == '\"' && !targetFound)
			{
				newRangeBeg = i;
				targetFound = true;
				i++;
			}
			//std::cout << line[i] << "  ";
			if (line[i] == '\"' && targetFound)
			{
				subTargetRange.beg = newRangeBeg;
				if (line[subTargetRange.beg - 3] != '8')//if range is argument of i18n function
				{
					subTargetRange.end = i + 1;
					return;
				}
				targetFound = false;
			}
		}
		subTargetRange.beg = -1;
		subTargetRange.end = -1;

	}


}


