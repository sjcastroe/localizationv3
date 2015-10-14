/*
 * LocalizationController.h
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#ifndef CONTROLLER_SRC_LOCALIZATIONCONTROLLER_SRC_LOCALIZATIONCONTROLLER_H_
#define CONTROLLER_SRC_LOCALIZATIONCONTROLLER_SRC_LOCALIZATIONCONTROLLER_H_

#include "../../Controller.h"
#include "../../../../Model/src/LocalizationModel/src/LocalizationModel.h"
#include <fstream>
#include <stdexcept>

namespace scastroController
{

class LocalizationController : public Controller
{
public:
	void run(int argc, char* argv[]);
private:
	std::string fileName;
};

}



#endif /* CONTROLLER_SRC_LOCALIZATIONCONTROLLER_SRC_LOCALIZATIONCONTROLLER_H_ */
