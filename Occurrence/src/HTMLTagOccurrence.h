/*
 * WildcardOccurrence.h
 *
 *  Created on: Oct 1, 2015
 *      Author: root
 */

#ifndef OCCURRENCE_SRC_HTMLTAGOCCURRENCE_H_
#define OCCURRENCE_SRC_HTMLTAGOCCURRENCE_H_


#include "Occurrence.h"
#include <string>
#include <stdexcept>
#include <tr1/memory>
#include <iostream>
#include <cctype>

namespace scastroOccurrence
{

	class HTMLTagOccurrence : public Occurrence
	{
	public:
		HTMLTagOccurrence();
		void handle(std::string& data);
		bool isFound();
		void feed(std::string li);
	private:
		void findSubRange();
		StrRange subTargetRange;
		bool echoedTag = false;
		bool inScriptTag = false;
		bool inPHPTag = false;
		bool inBegTag = false;
		bool inAlert = false;
		bool inTargetRange = false;
		bool subRangeExists = true;
		StrRange range;
	};

}


#endif /* OCCURRENCE_SRC_HTMLTAGOCCURRENCE_H_ */
