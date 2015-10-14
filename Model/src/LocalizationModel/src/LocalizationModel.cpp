/*
 * LocalizationModel.cpp
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#include "LocalizationModel.h"

namespace scastroModel
{
	void LocalizationModel::run()
	{

		if (intData.count("linenumber") == 0)
		{
			std::string eMessage = "The index \"linenumber\" does not exist.";
			std::runtime_error wrongArg(eMessage);
			throw wrongArg;
		}

		if (stringData.count("line") == 0)
		{
			std::string eMessage = "The index \"line\" does not exist.";
			std::runtime_error wrongArg(eMessage);
			throw wrongArg;
		}

		this->setOccurrences();

		if (occurrences.size() == 0)
		{
			std::string eMessage = "No occurrences have been set.";
			std::runtime_error noOccs(eMessage);
			throw noOccs;
		}

		for (unsigned int i = 0; i < occurrences.size(); i++)
		{
			//run seek occurrence for all occurrences. Seek occurrence should seek ALL the occurrences per line(may be more than one)
			if (Wildcard::eval(occurrences[i]->getOccurrence().c_str(), stringData["line"].c_str()))
			{
				//if what we're looking for is not in the line, we put the Model on alert until it finds the data we're looking for
				this->seekTargetData = true;
			}
				occurrences[i]->handle(stringData["line"]);
		}

	}

	void LocalizationModel::setOccurrences()
	{
		std::tr1::shared_ptr<Occurrence<std::string> > htmlTag(new HTMLTagOccurrence("*pear*"));
		occurrences.push_back(htmlTag);
	}
}


