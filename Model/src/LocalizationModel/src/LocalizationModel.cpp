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
			std::string line = stringData["line"];

			//find if line contains an occurrence or if an occurrence is in alert mode (the occurrence was found and needs more data to be handled)
			if (line.find(occurrences[i]->getOccurrence()) != -1 || occurrences[i]->inAlert())
				occurrences[i]->handle(stringData["line"]);
		}

	}

	void LocalizationModel::setOccurrences()
	{
		std::tr1::shared_ptr<Occurrence<std::string> > htmlTag(new CakeHTMLTagOccurrence("$this->Html->tag"));
		occurrences.push_back(htmlTag);
	}
}


