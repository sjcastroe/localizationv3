/*
 * LocalizationView.cpp
 *
 *  Created on: Oct 12, 2015
 *      Author: root
 */

#include "LocalizationView.h"

namespace scastroView
{

void LocalizationView::run()
{
	std::ofstream writeTo("tmpFile", std::ofstream::app);
	writeTo << model->getStringData("line") << std::endl;

	std::cout << model->getIntData("linenumber") << "   " << model->getStringData("line") << std::endl;
}

}


