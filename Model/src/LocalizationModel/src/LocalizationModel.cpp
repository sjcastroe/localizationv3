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

		if (stringData.count("filepath") == 0)
		{
			std::string eMessage = "The index \"filename\" does not exist.";
			std::runtime_error wrongArg(eMessage);
			throw wrongArg;
		}

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
	}

	void LocalizationModel::setSavedLine(int data)
	{
		savedLines.push_back(data);
	}

	int LocalizationModel::getSavedLine(int index)
	{
		if (index < savedLines.size() && index >= 0)
			return savedLines[index];
		else
			return -1;
	}
}


