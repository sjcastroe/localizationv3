/*
 * LocalizationController.h
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#ifndef CONTROLLER_SRC_LOCALIZATIONCONTROLLER_SRC_LOCALIZATIONCONTROLLER_H_
#define CONTROLLER_SRC_LOCALIZATIONCONTROLLER_SRC_LOCALIZATIONCONTROLLER_H_

#include <fstream>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <tr1/memory>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include "../../Controller.h"
#include "../../../../Model/src/LocalizationModel/src/LocalizationModel.h"

//Occurrence includes
#include "../../../../Occurrence/src/CakeHTMLTagOccurrence.h"
#include "../../../../Occurrence/src/HTMLTagOccurrence.h"
#include "../../../../Occurrence/src/I18nOccurrence.h"

//View messages includes
#include "../../../../Message/src/OccurrenceMessage.h"
#include "../../../../Message/src/OccurrenceLineMessage.h"
#include "../../../../Message/src/PromptMessage.h"
#include "../../../../Message/src/RepromptMessage.h"

using namespace scastroOccurrence;

namespace scastroController
{

class LocalizationController : public Controller
{
public:
	void run(int argc, char* argv[]);
private:
	std::string fileName;
	void setOccurrences();
	std::vector<std::tr1::shared_ptr<Occurrence> > occurrences;
};

}



#endif /* CONTROLLER_SRC_LOCALIZATIONCONTROLLER_SRC_LOCALIZATIONCONTROLLER_H_ */
