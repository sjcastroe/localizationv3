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

	char cCurrentPath[FILENAME_MAX];
	getcwd(cCurrentPath, sizeof(cCurrentPath));
	std::string filepath(cCurrentPath);
	model->setStringData("filepath", filepath + "/" + fileName);

	this->setOccurrences();

	std::ofstream* outputFile = new std::ofstream("tmpFile", std::ofstream::app);
	int lineNumber = 1;
	while (true)
	{
		std::string line;
		getline(readFrom, line);

		model->setIntData("linenumber", lineNumber);
		model->setStringData("line", line);
		model->run();

		for (unsigned int i = 0; i < occurrences.size(); i++)
		{
			//bool occAlertState = occurrences[i]->getAlertState();
			occurrences[i]->feed(line);

			//find if line contains an occurrence or if an occurrence is in alert mode (the occurrence was found and needs more data to be handled)
			if (occurrences[i]->isFound())
			{
				bool shouldBeHandled = true;

				//store unmodified line value
				std::string lineOrig = line;

				model->setStringData("occurrence", occurrences[i]->getOccurrenceType());
				model->setIntData("linenumber", lineNumber);
				model->setStringData("line", lineOrig);

				scastroView::Message* unhandledLine = new scastroView::OccurrenceLineMessage(model);
				unhandledLine->setExternalData("label", "Unhandled Occurrence");


				try
				{
					occurrences[i]->handle(line);
				}
				catch (std::exception& error)
				{

					model->setStringData("line", lineOrig);

					std::cout << "ERROR: Could not handle occurrence: " << error.what() << std::endl;
					view->display(new scastroView::OccurrenceMessage(model));
					view->display(unhandledLine);
					std::cout << "Press any key and then ENTER to continue." << std::endl;

					char anyKey;
					std::cin >> anyKey;

					std::cout << std::endl;
					shouldBeHandled = false;
				}


				if (line == lineOrig)
					shouldBeHandled = false;

				if (shouldBeHandled)
				{
					if (occurrences[i]->getOccurrenceType() == "I18n Wrapper")
					{
						model->setStringData("line", line);
					}
					else
					{
						view->display(new scastroView::OccurrenceMessage(model));

						view->display(unhandledLine);

						model->setStringData("line", line);

						scastroView::Message* handledLine = new scastroView::OccurrenceLineMessage(model);
						handledLine->setExternalData("label", "Handled Occurrence");

						view->display(handledLine);
						view->display(new scastroView::PromptMessage(model));


						bool validResponse = false;
						while (!validResponse)
						{
							char response;
							std::cin >> response;
							if (response == 'y')
								validResponse = true;
							else if (response == 'n')
							{
								validResponse = true;
								line = lineOrig;
								model->setStringData("line", line);
							}
							else
								std::cout << "Invalid output. Please try again.";
						}
						std::cout << std::endl;
					}
				}
			}
		}

		view->write(outputFile);

		lineNumber = lineNumber + 1;

		if (readFrom.eof())
			break;
	}

	readFrom.close();

	//change permissions and owner of copy file
	std::string changeOwner = "chown --reference=" + fileName + " tmpFile";
	std::string changePerm = "chmod --reference=" + fileName + " tmpFile";
	system(changeOwner.c_str());
	system(changePerm.c_str());

	//delete original file
	if (remove(fileName.c_str()) != 0)
	{
		std::string eMessage = "File " + fileName + " could not be deleted.";
		std::runtime_error fileNotDeleted(eMessage);
		throw fileNotDeleted;
	}

	//rename copy to original file name
	if (rename("tmpFile", fileName.c_str()) != 0)
	{
		std::string eMessage = "File tmpFile could not be renamed.";
		std::runtime_error renameFail(eMessage);
		throw renameFail;
	}

	delete outputFile;
}

void LocalizationController::setOccurrences()
{
	std::tr1::shared_ptr<Occurrence> cakeHtmlTag(new CakeHTMLTagOccurrence());
	occurrences.push_back(cakeHtmlTag);

	std::tr1::shared_ptr<Occurrence> htmlTag(new HTMLTagOccurrence());
	occurrences.push_back(htmlTag);

	//std::tr1::shared_ptr<Occurrence> i18nFunc(new I18nOccurrence());
	//occurrences.push_back(i18nFunc);

	std::tr1::shared_ptr<Occurrence> scriptTag(new ScriptTagOccurrence());
	occurrences.push_back(scriptTag);

	if (occurrences.size() == 0)
	{
		std::string eMessage = "No occurrences have been set.";
		std::runtime_error noOccs(eMessage);
		throw noOccs;
	}
}


}


