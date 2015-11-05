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
		int tagLevel = 0;
		int deltaTagLevel = 0;
		bool inPHPTag = false;
		StrRange range;
	};

}


#endif /* OCCURRENCE_SRC_HTMLTAGOCCURRENCE_H_ */
