/*
 * WildcardOccurrence.cpp
 *
 *  Created on: Oct 1, 2015
 *      Author: root
 */

#include <string>
#include "HTMLTagOccurrence.h"

namespace scastroOccurrence
{

	HTMLTagOccurrence::HTMLTagOccurrence(std::string occ) : Occurrence<std::string>::Occurrence(occ) {}

	void HTMLTagOccurrence::handle(std::string& data)
	{
		data = "hehehehehe";
	}


}


