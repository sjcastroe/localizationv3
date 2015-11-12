/*
 * LocalizationView.cpp
 *
 *  Created on: Oct 12, 2015
 *      Author: root
 */

#include "LocalizationView.h"

namespace scastroView
{

void LocalizationView::display(Message* message)
{
	message->output();
}

void LocalizationView::write(std::ofstream* file)
{
	*file << model->getStringData("line") << std::endl;
}

}
