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

	template<typename OccType>
	class Occurrence
	{
	public:
		Occurrence(OccType occ);
		virtual void handle(OccType& data) = 0;
		virtual bool getAlertState() const;
		virtual void offAlertState();
		virtual OccType getOccurrence() const;
		virtual ~Occurrence();
	protected:
		const OccType occurrence;
		std::string requestNextLine = "";
	};

}


#endif /* OCCURRENCE_SRC_OCCURRENCE_H_ */
