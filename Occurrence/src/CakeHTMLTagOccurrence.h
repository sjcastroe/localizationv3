/*
 * CakeHTMLTagOccurrence.h
 *
 *  Created on: Oct 16, 2015
 *      Author: root
 */

#ifndef OCCURRENCE_SRC_CAKEHTMLTAGOCCURRENCE_H_
#define OCCURRENCE_SRC_CAKEHTMLTAGOCCURRENCE_H_

#include "Occurrence.h"
#include <string>
#include <stdexcept>

namespace scastroOccurrence
{

	struct StrRange
	{
		int beg;
		int end;
	};

	class CakeHTMLTagOccurrence : public Occurrence<std::string>
	{
	public:
		CakeHTMLTagOccurrence(std::string occ);
		void handle(std::string& data);
		bool inAlert() const;
	private:
		StrRange getArg(const std::string line, StrRange& argRange);
		StrRange findArg(const std::string& line, std::string occurrence, int arg);
		std::string requestNextLine = "";
	};



}



#endif /* OCCURRENCE_SRC_CAKEHTMLTAGOCCURRENCE_H_ */
