/*
 * LocalizationMessage.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: root
 */

#include "OccurrenceLineMessage.h"

namespace scastroView
{
void OccurrenceLineMessage::output()
{
	std::cout << std::right << std::setw(25) << externalData["label"] << ": ";
	std::cout << std::right << std::setw(6) << model->getIntData("linenumber") << "|" << std::left << std::setw(20) << model->getStringData("line") << std::endl;
}

}


