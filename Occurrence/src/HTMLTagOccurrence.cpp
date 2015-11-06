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
	}

	void HTMLTagOccurrence::handle(std::string& data)
	{
		int rangeLength = range.end - range.beg;
		if (rangeLength < 0)
		{
			std::string eMessage = "The target range is negative.";
			std::runtime_error negTarRng(eMessage);
			throw negTarRng;
		}

		std::string dataMid = data.substr(range.beg, rangeLength);

		if (dataMid.find_first_not_of(' ') != std::string::npos)
		{
			std::string dataBeg = data.substr(0, range.beg);
			std::string dataEnd = data.substr(range.end);

			if (inPHPTag)
				data = dataBeg + "__('" + dataMid + "', true)" + dataEnd;
			else
				data = dataBeg + "<?php __('" + dataMid + "')?>" + dataEnd;
		}
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
				std::cout << "test" << std::endl;
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
					range.beg = i + 1;
			}

			//if in alert
			if (inAlert && i >= range.beg)
			{
				std::cout << "bullshit" <<  std::endl;
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
					std::cout << "range.beg: " << range.beg <<  std::endl;
					std::cout << "range.end: " << range.end <<  std::endl;
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


}


