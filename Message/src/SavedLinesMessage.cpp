/*
 * SavedLinesMessage.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: root
 */

#include "SavedLinesMessage.h"

namespace scastroView
{
void SavedLinesMessage::output()
{
	std::cout << "Saved Lines: ";

	int index = 0;
	int savedLine = model->getSavedLine(index);
	while(savedLine != -1)
	{
		std::cout << savedLine;

		index++;
		savedLine = model->getSavedLine(index);
		if (savedLine != -1)
			std::cout << ", ";
	}
	std::cout << std::endl;
}

}


