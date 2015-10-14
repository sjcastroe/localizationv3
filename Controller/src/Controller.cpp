/*
 * Controller.cpp
 *
 *  Created on: Oct 8, 2015
 *      Author: root
 */

#include "Controller.h"

namespace scastroController
{

void Controller::setModel(scastroModel::Model* m)
{
	model = m;
}

void Controller::setView(scastroView::View* v)
{
	view = v;
}

}


