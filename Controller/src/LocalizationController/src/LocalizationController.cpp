/*
 * LocalizationController.cpp
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#include "LocalizationController.h"

namespace scastroController
{

void LocalizationController::run(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::string eMessage = "Not enough command line arguments. A single argument specifying the file to localize should be used. Example: localizationv2 filename";
		std::runtime_error wrongArg(eMessage);
		throw wrongArg;
	}
	else if (argc > 2)
	{
		std::string eMessage = "Too many command line arguments. A single argument specifying the file to localize should be used. Example: localizationv2 filename";
		std::runtime_error wrongArg(eMessage);
		throw wrongArg;
	}

	fileName = argv[1];

	std::ifstream readFrom;
	readFrom.open(fileName.c_str());

	if (readFrom.is_open())
	{
	}
	else
	{
		std::string eMessage = "File " + fileName + " not found.";
		std::runtime_error fileNotFound(eMessage);
		throw fileNotFound;
	}

	int lineNumber = 1;
	while (true)
	{
		std::string line;
		getline(readFrom, line);

		if (readFrom.eof())
			break;

		model->setIntData("linenumber", lineNumber);
		model->setStringData("line", line);


		model->run();

		view->run();

		lineNumber = lineNumber + 1;
	}

	readFrom.close();
}


}


