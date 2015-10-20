/*
 * Occurrence.h
 *
 *  Created on: Oct 1, 2015
 *      Author: root
 */

#ifndef OCCURRENCE_SRC_OCCURRENCE_H_
#define OCCURRENCE_SRC_OCCURRENCE_H_

#include "../../Wildcard/src/Wildcard.h"

using scastroWildcard::Wildcard;

namespace scastroOccurrence
{

	template<typename OccType>
	class Occurrence
	{
	public:
		Occurrence(OccType occ);
		virtual void handle(OccType& data) = 0;
		virtual bool inAlert() const = 0;
		virtual OccType getOccurrence() const;
		virtual ~Occurrence();
	protected:
		const OccType occurrence;
	};

}


#endif /* OCCURRENCE_SRC_OCCURRENCE_H_ */
