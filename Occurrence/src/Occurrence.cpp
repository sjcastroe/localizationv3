/*
 * Occurrence.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: root
 */

#include "Occurrence.h"
#include <string>

namespace scastroOccurrence
{

	template<typename OccType>
	Occurrence<OccType>::Occurrence(OccType occ) : occurrence(occ) {}

	template<typename OccType>
	bool Occurrence<OccType>::getAlertState() const
	{
		if (requestNextLine == "")
			return false;
		else
			return true;
	}

	template<typename OccType>
	void Occurrence<OccType>::offAlertState()
	{
		requestNextLine = "";
	}

	template<typename OccType>
	OccType Occurrence<OccType>::getOccurrence() const
	{
		return occurrence;
	}

	template<typename OccType>
	Occurrence<OccType>::~Occurrence() {}

}

template class scastroOccurrence::Occurrence<std::string>;


