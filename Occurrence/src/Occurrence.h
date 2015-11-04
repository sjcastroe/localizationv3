/*
 * Occurrence.h
 *
 *  Created on: Oct 1, 2015
 *      Author: root
 */

#ifndef OCCURRENCE_SRC_OCCURRENCE_H_
#define OCCURRENCE_SRC_OCCURRENCE_H_

#include "../../Wildcard/src/Wildcard.h"
#include <string>

using scastroWildcard::Wildcard;

namespace scastroOccurrence
{
	struct StrRange
	{
		int beg;
		int end;
	};

	class Occurrence
	{
	public:
		virtual void handle(std::string& data) = 0;
		virtual bool isFound() = 0;
		virtual void feed(std::string li) = 0;
		virtual std::string getOccurrenceType() const;
		virtual ~Occurrence();
	protected:
		std::string occurrenceType;
		std::string line;
	};

}


#endif /* OCCURRENCE_SRC_OCCURRENCE_H_ */
