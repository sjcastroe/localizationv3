/*
 * InnerHTMLOccurrence.h
 *
 *  Created on: Nov 10, 2015
 *      Author: root
 */

#ifndef OCCURRENCE_SRC_JQUERYHTMLOCCURRENCE_H_
#define OCCURRENCE_SRC_JQUERYHTMLOCCURRENCE_H_

#include "Occurrence.h"
#include <string>
#include <stdexcept>
#include <iostream>

namespace scastroOccurrence
{

	class JQueryHTMLOccurrence : public Occurrence
	{
	public:
		JQueryHTMLOccurrence();
		void handle(std::string& data);
		bool isFound();
		void feed(std::string li);
	private:
		bool inAlert = false;
		StrRange range;
	};

}



#endif /* OCCURRENCE_SRC_JQUERYHTMLOCCURRENCE_H_ */
