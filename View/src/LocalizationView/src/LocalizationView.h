/*
 * LocalizationView.h
 *
 *  Created on: Oct 12, 2015
 *      Author: root
 */

#ifndef VIEW_SRC_LOCALIZATIONVIEW_SRC_LOCALIZATIONVIEW_H_
#define VIEW_SRC_LOCALIZATIONVIEW_SRC_LOCALIZATIONVIEW_H_

#include "../../View.h"
#include <iomanip>

namespace scastroView
{

class LocalizationView : public View
{
public:
	void display(Message* message);
	void write(std::ofstream* file);
};

}



#endif /* VIEW_SRC_LOCALIZATIONVIEW_SRC_LOCALIZATIONVIEW_H_ */
