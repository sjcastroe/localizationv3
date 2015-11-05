/*
 * I18nOccurrence.h
 *
 *  Created on: Nov 4, 2015
 *      Author: root
 */

#ifndef OCCURRENCE_SRC_I18NOCCURRENCE_H_
#define OCCURRENCE_SRC_I18NOCCURRENCE_H_

#include "Occurrence.h"
#include <string>
#include <stdexcept>

namespace scastroOccurrence
{

	class I18nOccurrence : public Occurrence
	{
	public:
		I18nOccurrence();
		void handle(std::string& data);
		bool isFound();
		void feed(std::string li);
	private:
		StrRange range;
	};

}



#endif /* OCCURRENCE_SRC_I18NOCCURRENCE_H_ */
