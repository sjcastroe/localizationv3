/*
 * CakeHTMLTagOccurrence.h
 *
 *  Created on: Oct 16, 2015
 *      Author: root
 */

#ifndef OCCURRENCE_SRC_CAKEHTMLTAGOCCURRENCE_H_
#define OCCURRENCE_SRC_CAKEHTMLTAGOCCURRENCE_H_

#include "Occurrence.h"
#include <stdexcept>
#include "../../Wildcard/src/Wildcard.h"

namespace scastroOccurrence
{

	class CakeHTMLTagOccurrence : public Occurrence<std::string>
	{
	public:
		CakeHTMLTagOccurrence(std::string occ);
		void handle(std::string& data);
	private:
		StrRange getArg(const std::string line, StrRange& argRange);
		StrRange findArg(const std::string& line, std::string occurrence, int arg);
	};



}



#endif /* OCCURRENCE_SRC_CAKEHTMLTAGOCCURRENCE_H_ */
