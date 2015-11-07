/*
 * main.cpp
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#include "Model/src/LocalizationModel/src/LocalizationModel.h"
#include "View/src/LocalizationView/src/LocalizationView.h"
#include "Controller/src/LocalizationController/src/LocalizationController.h"

using namespace scastroModel;
using namespace scastroView;
using namespace scastroController;

//Command Line Arguments: 1)file to read
int main(int argc, char* argv[])
{
	Model* model = new LocalizationModel();
	View* view = new LocalizationView();
	Controller* controller = new LocalizationController();

	try
	{
		view->setModel(model);

		controller->setModel(model);
		controller->setView(view);

		controller->run(argc, argv);

		delete model;
		delete view;
		delete controller;

	}
	catch(std::exception& error)
	{
		std::cout << error.what();
		delete model;
		delete view;
		delete controller;
	}

	return 0;
}


