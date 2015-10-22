/*
 * PromptMessage.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: root
 */

#include "OccurrenceMessage.h"

namespace scastroView
{
void OccurrenceMessage::output()
{
	std::cout << model->getStringData("filepath") << std::endl;
	std::cout << "An occurrence has been found of type: " << model->getStringData("occurrence") << std::endl;
}

}


